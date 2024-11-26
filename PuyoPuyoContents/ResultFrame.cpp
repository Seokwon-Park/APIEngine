#include "aepch.h"
#include "ResultFrame.h"

AResultFrame::AResultFrame()
{
	Frames.resize(8, nullptr);
	FrameAnimator.resize(8, nullptr);
	for (int i = 0; i < Frames.size(); i++)
	{
		FrameAnimator[i] = CreateDefaultSubobject<UAnimatorComponent>("");
		Frames[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
		Frames[i]->SetSprite("LVFrame", i);
		Frames[i]->SetComponentScale(FrameScale[i]);
		Frames[i]->SetComponentLocation(FrameLoc[i]);
		Frames[i]->SetPivot(EPivotType::TopLeft);
		Frames[i]->SetRemoveColor(UColor(136, 102, 102, 0));
		Frames[i]->SetAnimator(FrameAnimator[i]);

		FrameAnimator[i]->CreateAnimation("Expand", "LVFrame", { i,i,i,i,i,i }, 0.1f, false);
	}

	FrameAnimator[0]->SetAnimationEvent("Expand", 1, [this]() { Frames[0]->SetComponentLocation(Frames[0]->GetComponentLocation() - FVector2D(0.0f, 32.0f)); });
	FrameAnimator[1]->SetAnimationEvent("Expand", 1, [this]() { Frames[1]->SetComponentLocation(Frames[1]->GetComponentLocation() - FVector2D(0.0f, 32.0f)); });
	FrameAnimator[2]->SetAnimationEvent("Expand", 1, [this]() { Frames[2]->SetComponentLocation(Frames[2]->GetComponentLocation() + FVector2D(0.0f, 32.0f)); });
	FrameAnimator[3]->SetAnimationEvent("Expand", 1, [this]() { Frames[3]->SetComponentLocation(Frames[3]->GetComponentLocation() + FVector2D(0.0f, 32.0f)); });
	FrameAnimator[4]->SetAnimationEvent("Expand", 1, [this]() 
		{
			Frames[4]->SetComponentLocation(Frames[4]->GetComponentLocation() - FVector2D(0.0f, 32.0f)); 
			Frames[4]->SetComponentScale(Frames[4]->GetComponentScale()+FVector2D(0.0f,64.0f));
		});
	FrameAnimator[5]->SetAnimationEvent("Expand", 1, [this]() { Frames[5]->SetComponentLocation(Frames[5]->GetComponentLocation() + FVector2D(0.0f, 32.0f)); });
	FrameAnimator[6]->SetAnimationEvent("Expand", 1, [this]() { Frames[6]->SetComponentLocation(Frames[6]->GetComponentLocation() - FVector2D(0.0f, 32.0f)); });
	FrameAnimator[7]->SetAnimationEvent("Expand", 1, [this]() { 
		Frames[7]->SetComponentLocation(Frames[7]->GetComponentLocation() - FVector2D(0.0f, 32.0f));
		Frames[7]->SetComponentScale(Frames[7]->GetComponentScale() + FVector2D(0.0f, 64.0f));

		});


	FrameAnimator[0]->SetAnimationEvent("Expand", 2, [this]() { Frames[0]->SetComponentLocation(Frames[0]->GetComponentLocation() - FVector2D(0.0f, 16.0f)); });
	FrameAnimator[1]->SetAnimationEvent("Expand", 2, [this]() { Frames[1]->SetComponentLocation(Frames[1]->GetComponentLocation() - FVector2D(0.0f, 16.0f)); });
	FrameAnimator[2]->SetAnimationEvent("Expand", 2, [this]() { Frames[2]->SetComponentLocation(Frames[2]->GetComponentLocation() + FVector2D(0.0f, 16.0f)); });
	FrameAnimator[3]->SetAnimationEvent("Expand", 2, [this]() { Frames[3]->SetComponentLocation(Frames[3]->GetComponentLocation() + FVector2D(0.0f, 16.0f)); });
	FrameAnimator[4]->SetAnimationEvent("Expand", 2, [this]()
		{
			Frames[4]->SetComponentLocation(Frames[4]->GetComponentLocation() - FVector2D(0.0f, 16.0f));
			Frames[4]->SetComponentScale(Frames[4]->GetComponentScale() + FVector2D(0.0f, 32.0f));
		});
	FrameAnimator[5]->SetAnimationEvent("Expand", 2, [this]() { Frames[5]->SetComponentLocation(Frames[5]->GetComponentLocation() + FVector2D(0.0f, 16.0f)); });
	FrameAnimator[6]->SetAnimationEvent("Expand", 2, [this]() { Frames[6]->SetComponentLocation(Frames[6]->GetComponentLocation() - FVector2D(0.0f, 16.0f)); });
	FrameAnimator[7]->SetAnimationEvent("Expand", 2, [this]() {
		Frames[7]->SetComponentLocation(Frames[7]->GetComponentLocation() - FVector2D(0.0f, 16.0f));
		Frames[7]->SetComponentScale(Frames[7]->GetComponentScale() + FVector2D(0.0f, 32.0f));

		});


	FrameAnimator[0]->SetAnimationEvent("Expand", 3, [this]() { Frames[0]->SetComponentLocation(Frames[0]->GetComponentLocation() - FVector2D(0.0f, 32.0f)); });
	FrameAnimator[1]->SetAnimationEvent("Expand", 3, [this]() { Frames[1]->SetComponentLocation(Frames[1]->GetComponentLocation() - FVector2D(0.0f, 32.0f)); });
	FrameAnimator[2]->SetAnimationEvent("Expand", 3, [this]() { Frames[2]->SetComponentLocation(Frames[2]->GetComponentLocation() + FVector2D(0.0f, 32.0f)); });
	FrameAnimator[3]->SetAnimationEvent("Expand", 3, [this]() { Frames[3]->SetComponentLocation(Frames[3]->GetComponentLocation() + FVector2D(0.0f, 32.0f)); });
	FrameAnimator[4]->SetAnimationEvent("Expand", 3, [this]()
		{
			Frames[4]->SetComponentLocation(Frames[4]->GetComponentLocation() - FVector2D(0.0f, 32.0f));
			Frames[4]->SetComponentScale(Frames[4]->GetComponentScale() + FVector2D(0.0f, 64.0f));
		});
	FrameAnimator[5]->SetAnimationEvent("Expand", 3, [this]() { Frames[5]->SetComponentLocation(Frames[5]->GetComponentLocation() + FVector2D(0.0f, 32.0f)); });
	FrameAnimator[6]->SetAnimationEvent("Expand", 3, [this]() { Frames[6]->SetComponentLocation(Frames[6]->GetComponentLocation() - FVector2D(0.0f, 32.0f)); });
	FrameAnimator[7]->SetAnimationEvent("Expand", 3, [this]() {
		Frames[7]->SetComponentLocation(Frames[7]->GetComponentLocation() - FVector2D(0.0f, 32.0f));
		Frames[7]->SetComponentScale(Frames[7]->GetComponentScale() + FVector2D(0.0f, 64.0f));

		});

	FrameAnimator[0]->SetAnimationEvent("Expand", 4, [this]() { Frames[0]->SetComponentLocation(Frames[0]->GetComponentLocation() - FVector2D(0.0f, 48.0f)); });
	FrameAnimator[1]->SetAnimationEvent("Expand", 4, [this]() { Frames[1]->SetComponentLocation(Frames[1]->GetComponentLocation() - FVector2D(0.0f, 48.0f)); });
	FrameAnimator[2]->SetAnimationEvent("Expand", 4, [this]() { Frames[2]->SetComponentLocation(Frames[2]->GetComponentLocation() + FVector2D(0.0f, 48.0f)); });
	FrameAnimator[3]->SetAnimationEvent("Expand", 4, [this]() { Frames[3]->SetComponentLocation(Frames[3]->GetComponentLocation() + FVector2D(0.0f, 48.0f)); });
	FrameAnimator[4]->SetAnimationEvent("Expand", 4, [this]()
		{
			Frames[4]->SetComponentLocation(Frames[4]->GetComponentLocation() - FVector2D(0.0f, 48.0f));
			Frames[4]->SetComponentScale(Frames[4]->GetComponentScale() + FVector2D(0.0f, 96.0f));
		});
	FrameAnimator[5]->SetAnimationEvent("Expand", 4, [this]() { Frames[5]->SetComponentLocation(Frames[5]->GetComponentLocation() + FVector2D(0.0f, 48.0f)); });
	FrameAnimator[6]->SetAnimationEvent("Expand", 4, [this]() { Frames[6]->SetComponentLocation(Frames[6]->GetComponentLocation() - FVector2D(0.0f, 48.0f)); });
	FrameAnimator[7]->SetAnimationEvent("Expand", 4, [this]() {
		Frames[7]->SetComponentLocation(Frames[7]->GetComponentLocation() - FVector2D(0.0f, 48.0f));
		Frames[7]->SetComponentScale(Frames[7]->GetComponentScale() + FVector2D(0.0f, 96.0f));
		});

	//
	FrameAnimator[0]->SetAnimationEvent("Expand", 5, [this]() { Frames[0]->SetComponentLocation(Frames[0]->GetComponentLocation() - FVector2D(0.0f, 16.0f)); });
	FrameAnimator[1]->SetAnimationEvent("Expand", 5, [this]() { Frames[1]->SetComponentLocation(Frames[1]->GetComponentLocation() - FVector2D(0.0f, 16.0f)); });
	FrameAnimator[4]->SetAnimationEvent("Expand", 5, [this]()
		{
			Frames[4]->SetComponentLocation(Frames[4]->GetComponentLocation() - FVector2D(0.0f, 16.0f));
			Frames[4]->SetComponentScale(Frames[4]->GetComponentScale() + FVector2D(0.0f, 16.0f));
		});
	FrameAnimator[6]->SetAnimationEvent("Expand", 5, [this]() { Frames[6]->SetComponentLocation(Frames[6]->GetComponentLocation() - FVector2D(0.0f, 16.0f)); });
	FrameAnimator[7]->SetAnimationEvent("Expand", 5, [this]() {
		Frames[7]->SetComponentLocation(Frames[7]->GetComponentLocation() - FVector2D(0.0f, 16.0f));
		Frames[7]->SetComponentScale(Frames[7]->GetComponentScale() + FVector2D(0.0f, 16.0f));
		});


	for (int i = 0; i < Frames.size(); i++)
	{
		FrameAnimator[i]->ChangeAnimation("Expand");
	}
}

AResultFrame::~AResultFrame()
{
}


void AResultFrame::OpenFrame()
{
	for (int i = 0; i < Frames.size(); i++)
	{
		FrameAnimator[i]->ChangeAnimation("Expand");
	}
}


void AResultFrame::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AResultFrame::BeginPlay()
{
	Super::BeginPlay();


}
