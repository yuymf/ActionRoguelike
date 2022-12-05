// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASDashProjectile::ASDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDeley = 0.2f;

	MovementComp->InitialSpeed = 6000.0f;
}

void ASDashProjectile::Explode_Implementation()
{
	// Clear timer if the Explode was already called through another source like OnActorHit
	GetWorldTimerManager().ClearTimer(TimeHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation()); // can be found in MagicProjectileBP

	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	// do not destroy(), to set a 2rd timer
	FTimerHandle TimeHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimeHandle_DelayedTeleport, this, &ASDashProjectile::TeleportInstigator, TeleportDelay);

	// Skip base implementation as it will destroy actor (we need to stay alive a bit longer to finish the 2nd timer)
	//Super::Explode_Implementation();
}

void ASDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		// Keep instigator rotation or it may end up jarring
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);	// 传送
	}

	Destroy();
}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	// 到爆炸时间后，触发Explode()
	GetWorldTimerManager().SetTimer(TimeHandle_DelayedDetonate, this, &ASDashProjectile::Explode, DetonateDeley);
}

