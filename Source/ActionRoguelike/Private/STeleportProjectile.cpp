// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASTeleportProjectile::ASTeleportProjectile()
{
	DestroyEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("DestroyEffect"));
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportProjectile,this, &ASTeleportProjectile::ProjectileResolve, 0.2f);
}

void ASTeleportProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != GetInstigator())
	{
		ProjectileResolve();
	}
}

void ASTeleportProjectile::ProjectileResolve()
{
	// Stop Projectile
	MovementComp->SetActive(false);

	// Play Destroy Particle Effect
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyEffect, GetActorLocation(), GetActorRotation());
	// Waiting .2 seconds before teleporting the player and destroying yourself
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportProjectile,this, &ASTeleportProjectile::TeleportInstigator, 0.2f);
}

void ASTeleportProjectile::TeleportInstigator()
{
	GetInstigator()->TeleportTo(GetActorLocation(),GetInstigator()->GetActorRotation());
	Destroy();
}