// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMagicProjectile.h"
#include "STeleportProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASTeleportProjectile : public ASMagicProjectile
{
	GENERATED_BODY()
	
public:	
	ASTeleportProjectile();
protected:
	FTimerHandle TimerHandle_TeleportProjectile;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* DestroyEffect;
	
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void TeleportInstigator();

	UFUNCTION()
	void ProjectileResolve();
};
