using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PhysicsEngine : MonoBehaviour
{
    public float groundedTol = 0.05f;

    public struct CollisionPair{
        public PhysicsRBody rigidBodyA;
        public PhysicsRBody rigidBodyB;
    }

    public struct CollisionInfo{
        public Vector2 collisionNormal;
        public float penetration;
    }

    private Dictionary<CollisionPair, CollisionInfo> collisions = new Dictionary<CollisionPair, CollisionInfo>();
    private List<PhysicsRBody> rigidBodies = new List<PhysicsRBody>();

    public void AddRigidBody(PhysicsRBody rigidBody){
        rigidBodies.Add(rigidBody);
    }

    void IntegrateBodies(float dT){
        foreach (PhysicsRBody rb in rigidBodies){
            rb.Integrate(dT);
        }
    }

    public bool IsGrounded(PhysicsRBody rigidBody){
        foreach (PhysicsRBody rb in rigidBodies){
            if (rb != rigidBody){
                if (rigidBody.aabb.bLeft.x < rb.aabb.tRight.x 
                    && rigidBody.aabb.tRight.x > rb.aabb.bLeft.x
                    && Mathf.Abs(rigidBody.aabb.bLeft.y - rb.aabb.tRight.y) <= groundedTol){
                    if (Mathf.Abs(rigidBody.currentVelocity.y) < groundedTol)
                        return true;
                }
            }
        }
        return false;
    }

    void CheckCollisions(){
        foreach (PhysicsRBody bodyA in rigidBodies.GetRange(0, rigidBodies.Count - 1)){
            foreach (PhysicsRBody bodyB in rigidBodies.GetRange(rigidBodies.IndexOf(bodyA), rigidBodies.Count - rigidBodies.IndexOf(bodyA))){
                if (bodyA != bodyB){
                    CollisionPair pair = new CollisionPair();
                    CollisionInfo colInfo = new CollisionInfo();
                    pair.rigidBodyA = bodyA; pair.rigidBodyB = bodyB;

                    Vector2 distance = bodyB.transform.position - bodyA.transform.position;

                    Vector2 halfSizeA = (bodyA.aabb.tRight - bodyA.aabb.bLeft) / 2;
                    Vector2 halfSizeB = (bodyB.aabb.tRight - bodyB.aabb.bLeft) / 2;

                    Vector2 gap = new Vector2(Mathf.Abs(distance.x), Mathf.Abs(distance.y)) - (halfSizeA + halfSizeB);

                    // Seperating Axis Theorem test
                    if (gap.x < 0 && gap.y < 0){                                                 
                        Debug.Log("Collided!!!");

                        if (collisions.ContainsKey(pair)){
                            collisions.Remove(pair);
                        }
                        //more horizontal dist
                        if (gap.x > gap.y){
                            //body1 is to the right of body2
                            if (distance.x > 0){
                                colInfo.collisionNormal = new Vector2(1, 0);
                                // ... Update collision normal
                            }
                            //body1 is to the left of body2
                            else {
                                colInfo.collisionNormal = new Vector2(-1, 0);
                                // ... Update collision normal
                            }                                
                            colInfo.penetration = gap.x;    
                        }
                        //more vertical distance
                        else{
                            //body1 is above body2
                            if (distance.y > 0) {
                                colInfo.collisionNormal = new Vector2(0, 1);
                                // ... Update collision normal
                            }               
                            //body1 is below body2
                            else {
                                colInfo.collisionNormal = new Vector2(0, -1);
                                // ... Update collision normal
                            }
                            colInfo.penetration = gap.y; 
                        }                                 
                        collisions.Add(pair, colInfo);
                    }
                    else if (collisions.ContainsKey(pair)){
                        Debug.Log("removed");
                        collisions.Remove(pair);
                    }

                }
            }
        }
    }

    void ResolveCollisions(){
        foreach (CollisionPair pair in collisions.Keys){
            float minBounce = Mathf.Min(pair.rigidBodyA.bounciness, pair.rigidBodyB.bounciness);
            float velAlongNormal = Vector2.Dot(pair.rigidBodyB.currentVelocity - pair.rigidBodyA.currentVelocity, collisions[pair].collisionNormal);
            if (velAlongNormal > 0) continue;

            float j = -(1 + minBounce) * velAlongNormal;
            float invMassA, invMassB;
            if (pair.rigidBodyA.mass == 0)
                invMassA = 0;
            else
                invMassA = 1 / pair.rigidBodyA.mass;

            if (pair.rigidBodyB.mass == 0)
                invMassB = 0;
            else
                invMassB = 1 / pair.rigidBodyB.mass;

            j /= invMassA + invMassB;

            Vector2 impulse = j * collisions[pair].collisionNormal;

            // ... update velocities

            pair.rigidBodyA.currentVelocity -= impulse;
            if (pair.rigidBodyB.moveable)
                pair.rigidBodyB.currentVelocity += impulse;

            if (Mathf.Abs(collisions[pair].penetration) > 0.01f){
                 PositionalCorrection(pair);
            }
        }
    }

    /*
    * ______________ Why do we need this function? 
    * Corrects the object from sticking into each other
    * Tries to move the object out of the objects it is stuck in
    * ______________ Try taking it out and see what happens
    */
    void PositionalCorrection(CollisionPair c){
        const float percent = 0.2f;
                            
        float invMassA, invMassB;
        if (c.rigidBodyA.mass == 0)
            invMassA = 0;
        else
            invMassA = 1 / c.rigidBodyA.mass;

        if (c.rigidBodyB.mass == 0)
            invMassB = 0;
        else
            invMassB = 1 / c.rigidBodyB.mass;

        Vector2 correction = ((collisions[c].penetration / (invMassA + invMassB)) * percent) * -collisions[c].collisionNormal;

        Vector2 temp = c.rigidBodyA.transform.position;
        temp -= invMassA * correction;
        c.rigidBodyA.transform.position = temp;

        temp = c.rigidBodyB.transform.position;
        temp += invMassB * correction;
        c.rigidBodyB.transform.position = temp;
    }

    void UpdatePhysics(){
        CheckCollisions();
        ResolveCollisions();
        IntegrateBodies(Time.deltaTime);
    }

    // Update is called once per frame
    void FixedUpdate(){
        UpdatePhysics();
    }
}
