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
		UE_LOG(LogTemp, Display, TEXT("Unlocking : %s"), *Actor->GetActorNameOrLabel());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Relocking"));
	}

}

AActor* UTriggerComponent::GetAcceptableActor() const
{	
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		UE_LOG(LogTemp, Display, TEXT("ActorName : %s"), *Actor->GetActorNameOrLabel());
		if (Actor->ActorHasTag(AcceptableActorTag))
		{
			return Actor;
		}
	}
	return nullptr;
}