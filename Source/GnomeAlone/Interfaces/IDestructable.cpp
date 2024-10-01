// Fill out your copyright notice in the Description page of Project Settings.


#include "IDestructable.h"

// Add default functionality here for any IIDestructable functions that are not pure virtual.
void IIDestructable::Destroy_Implementation(AActor* Destroyer, AActor* Destroyed)
{
	Destroy(Destroyer, Destroyed);
}
