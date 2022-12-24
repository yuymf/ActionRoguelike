// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;
class USoundCue;
//class UCameraShake;

//1.UCLASS(abstract) ��Abstract�����η���������Ϊ��������ࡱ����������ֹ�û�����ñ༭������������������������Actor����������Ϸ�����д���������ʵ����
//2.UCLASS(blueprintable) ��ָ������Ϊ������ͼ�Ŀɽ��ܻ��ࡣ
//3.UCLASS(ClassGroup = GroupName) ����ʾ��ñ༭����Actor�������Actor�����������Group View������ͼ����ʱ��Ӧ����ָ����GroupName�������ƣ��а�������༰���������ࡣ
//4.UCLASS(const) :�����е��������Լ�������Ϊ��������Ӧ��Ϊ����������
//5.UCLASS(Deprecated) : �����ѱ����������Ҹ���Ķ��������л�ʱ�����ᱻ���档
//6.UCLASS(showFunctions = FunctionName) : ��������ͼ����ʾָ���ĺ�����

UCLASS(ABSTRACT) // 'ABSTRACT' marks this class as incomplete, keeping this out of certain dropdowns windows like SpawnActor in Unreal Editor
class ACTIONROGUELIKE_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectileBase();

protected:
	
	// ����ϵͳ
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;

	// ���ҡ��
	//UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	//TSubclassOf<UCameraShake> ImpactShake;

	//UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	//float ImpactShakeInnerRadius;

	//UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	//float ImpactShakeOuterRadius;

	// ��Ƶ
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* ImpactSound;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAudioComponent* AudioComp;

	// ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;
	
	// �������ƶ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	// ����Ч��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// BlueprintNativeEvent = C++ base implementation, can be expanded in Blueprints
	// BlueprintCallable to allow child classes to trigger explosions
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;
};
