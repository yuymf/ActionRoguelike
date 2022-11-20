// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:

	//Í°
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	//±¬Õ¨Á¦
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* ForceComp;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void OnActorHit(UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
