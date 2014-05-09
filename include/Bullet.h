#pragma once
#include <irrlicht/irrlicht.h>
#include <bullet/btBulletDynamicsCommon.h>

using namespace irr;

class Bullet{
public:
    Bullet();
    ~Bullet();
    void UpdatePhysics(u32 TDeltaTime);
    btRigidBody* AddBox(scene::ISceneNode* node, double mass, bool isKinematic = false);
    btRigidBody* AddSphere(scene::ISceneNode* node, float radius, double mass, bool isKinematic = false);
private:
    btRigidBody* Add(scene::ISceneNode* node, double mass, btCollisionShape *Shape, bool isKinematic);
    btCollisionShape* GetSphereShape(float radius);
    btCollisionShape* GetBoxShape(scene::ISceneNode* node);
    void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler);
    void ClearObjects();
    btDiscreteDynamicsWorld *World;
    core::list<btRigidBody *> Objects;
    btBroadphaseInterface *BroadPhase;
    btDefaultCollisionConfiguration *CollisionConfiguration;
    btCollisionDispatcher *Dispatcher;
    btSequentialImpulseConstraintSolver *Solver;
};
