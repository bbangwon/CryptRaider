// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Trigger Component Alive"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();

	if (Actor != nullptr)
	{
		//Cast Actor->GetRootComponent()가 UPrimitiveComponent*인지 확인
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Component->SetSimulatePhysics(false);
		}

		Mover->SetShouldMove(true);		
	}
	else
	{
		Mover->SetShouldMove(false);
	}

}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{	
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		UE_LOG(LogTemp, Display, TEXT("ActorName : %s"), *Actor->GetActorNameOrLabel());
		bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if (HasAcceptableTag && !IsGrabbed)
		{
			return Actor;
		}
	}
	return nullptr;
}
