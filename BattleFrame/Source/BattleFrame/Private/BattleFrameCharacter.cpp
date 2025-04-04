/*
* BattleFrame
* Created: 2025
* Author: Leroy Works, All Rights Reserved.
*/

#include "BattleFrameCharacter.h"
#include "Traits/Hero.h"
#include "Traits/Health.h"
#include "Traits/Avoiding.h"
#include "Traits/Located.h"
#include "Traits/Collider.h"
#include "Traits/Statistics.h"
#include "Traits/BindFlowField.h"

// Sets default values
ABattleFrameCharacter::ABattleFrameCharacter()
{
	Subjective = CreateDefaultSubobject<USubjectiveActorComponent>("Subjective");

	Subjective->SetTrait(FHero{});
	Subjective->SetTrait(FHealth{});
	Subjective->SetTrait(FCollider{});
	Subjective->SetTrait(FStatistics{});
	Subjective->SetTrait(FBindFlowField{});

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABattleFrameCharacter::BeginPlay()
{
	Super::BeginPlay();

	// if missing, add these traits
	Subjective->ObtainTrait<FHealth>();
	Subjective->SetTrait(FLocated{ GetActorLocation() });

	const auto Handle = Subjective->GetHandle();
	const auto Collider = Subjective->ObtainTrait<FCollider>();
	Subjective->SetTrait(FAvoiding{ GetActorLocation(),Collider.Radius, Handle, Handle.CalcHash() });
}

// Called every frame
void ABattleFrameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Subjective->GetTraitPtr<FLocated, EParadigm::Unsafe>()->Location = GetActorLocation();
}

// Called to bind functionality to input
void ABattleFrameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

