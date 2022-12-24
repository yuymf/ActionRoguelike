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

//1.UCLASS(abstract) ：Abstract类修饰符将类声明为“抽象基类”，这样会阻止用户在虚幻编辑器中向这个世界中添加这个类的Actor，或者在游戏过程中创建这个类的实例。
//2.UCLASS(blueprintable) ：指定该类为创建蓝图的可接受基类。
//3.UCLASS(ClassGroup = GroupName) ：表示虚幻编辑器的Actor浏览器在Actor浏览器中启用Group View（组视图）的时候应该在指定的GroupName（组名称）中包括这个类及其所有子类。
//4.UCLASS(const) :本类中的所有属性及函数均为常量，并应作为常量导出。
//5.UCLASS(Deprecated) : 该类已被废弃，并且该类的对象在序列化时将不会被保存。
//6.UCLASS(showFunctions = FunctionName) : 在属性视图中显示指定的函数。

UCLASS(ABSTRACT) // 'ABSTRACT' marks this class as incomplete, keeping this out of certain dropdowns windows like SpawnActor in Unreal Editor
class ACTIONROGUELIKE_API ASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASProjectileBase();

protected:
	
	// 粒子系统
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;

	// 相机摇晃
	//UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	//TSubclassOf<UCameraShake> ImpactShake;

	//UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	//float ImpactShakeInnerRadius;

	//UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	//float ImpactShakeOuterRadius;

	// 音频
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* ImpactSound;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAudioComponent* AudioComp;

	// 球
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;
	
	// 发射体移动
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	// 粒子效果
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
