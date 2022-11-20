// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	//ģ������
	MeshComp->SetSimulatePhysics(true);
	//MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetAutoActivate(false);
	ForceComp->SetupAttachment(MeshComp);
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

	// ��������
	ForceComp->Radius = 750.0f;					//��ը�뾶
	ForceComp->ImpulseStrength = 2500.0f;		//�����
	ForceComp->bImpulseVelChange = true;		//������������

}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//�������Ļ�����Ҫ��OnActorHit���봫��
	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	// �����ַ�����Ҫ����*�� %s = string, %f = float;
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);

	// Detailed info on logging in ue4
	// https://nerivec.github.io/old-ue4-wiki/pages/logs-printing-messages-to-yourself-during-runtime.html
}



