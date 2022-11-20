// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	//模拟物理
	MeshComp->SetSimulatePhysics(true);
	//MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetAutoActivate(false);
	ForceComp->SetupAttachment(MeshComp);
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

	// 力场属性
	ForceComp->Radius = 750.0f;					//爆炸半径
	ForceComp->ImpulseStrength = 2500.0f;		//冲击力
	ForceComp->bImpulseVelChange = true;		//忽略物体质量

}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//编译错误的话，需要在OnActorHit加入传参
	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();
}



