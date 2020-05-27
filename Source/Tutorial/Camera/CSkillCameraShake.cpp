// Fill out your copyright notice in the Description page of Project Settings.


#include "CSkillCameraShake.h"

UCSkillCameraShake::UCSkillCameraShake()
{
	
	OscillationDuration = 0.15f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.2f;

	LocOscillation.Y.Amplitude = 100.f;
	LocOscillation.Y.Frequency = 100.f;
	LocOscillation.Y.Waveform =EOscillatorWaveform::PerlinNoise;


	LocOscillation.Z.Amplitude = 100.f;
	LocOscillation.Z.Frequency = 100.f;
	LocOscillation.Z.Waveform = EOscillatorWaveform::PerlinNoise;
}