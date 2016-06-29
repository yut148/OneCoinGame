/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2013 Erwin Coumans  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BT_MULTIBODY_SOLVER_CONSTRAINT_H
#define BT_MULTIBODY_SOLVER_CONSTRAINT_H

#include "bullet/LinearMath/btVector3.h"
#include "bullet/LinearMath/btAlignedObjectArray.h"

class btMultiBody;
#include "bullet/BulletDynamics/ConstraintSolver/btSolverBody.h"
#include "bullet/BulletDynamics/ConstraintSolver/btContactSolverInfo.h"

///1D constraint along a normal axis between bodyA and bodyB. It can be combined to solve contact and friction constraints.
ATTRIBUTE_ALIGNED16 (struct)	btMultiBodySolverConstraint
{
	BT_DECLARE_ALIGNED_ALLOCATOR();


	int				m_deltaVelAindex;//more generic version of m_relpos1CrossNormal/m_contactNormal1
	btVector3		m_relpos1CrossNormal;
	btVector3		m_contactNormal1;
	int				m_jacAindex;

	int				m_deltaVelBindex;
	btVector3		m_relpos2CrossNormal;
	btVector3		m_contactNormal2; //usually m_contactNormal2 == -m_contactNormal1, but not always
	int				m_jacBindex;

	btVector3		m_angularComponentA;
	btVector3		m_angularComponentB;
	
	mutable btSimdScalar	m_appliedPushImpulse;
	mutable btSimdScalar	m_appliedImpulse;

	btScalar	m_friction;
	btScalar	m_jacDiagABInv;
	btScalar		m_rhs;
	btScalar		m_cfm;
	
    btScalar		m_lowerLimit;
	btScalar		m_upperLimit;
	btScalar		m_rhsPenetration;
    union
	{
		void*		m_originalContactPoint;
		btScalar	m_unusedPadding4;
	};

	int	m_overrideNumSolverIterations;
    int			m_frictionIndex;

	int m_solverBodyIdA;
	btMultiBody* m_multiBodyA;
	int			m_linkA;
	
	int m_solverBodyIdB;
	btMultiBody* m_multiBodyB;
	int			m_linkB;

	enum		btSolverConstraintType
	{
		BT_SOLVER_CONTACT_1D = 0,
		BT_SOLVER_FRICTION_1D
	};
};

typedef btAlignedObjectArray<btMultiBodySolverConstraint>	btMultiBodyConstraintArray;

#endif //BT_MULTIBODY_SOLVER_CONSTRAINT_H
