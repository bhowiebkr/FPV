// Fill out your copyright notice in the Description page of Project Settings.


#include "FPVPawn.h"

#include "Windows/MinWindows.h"
#include <Dbt.h>
#include <hidsdi.h>
#include <hidpi.h>



// Sets default values
AFPVPawn::AFPVPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPVPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPVPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPVPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

