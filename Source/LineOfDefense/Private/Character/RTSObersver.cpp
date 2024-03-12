// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RTSObersver.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ARTSObersver::ARTSObersver()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARTSObersver::BeginPlay()
{
	Super::BeginPlay();
}

FVector ARTSObersver::CalculaterMoveDirection()
{
    FVector MoveDirection;
	
	FVector2D ViewportCenterPoint = UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld()).GetLocalSize()/2;
	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	float BorderLength = 20;

	/*
	 * 接下来需要判断鼠标是否到达屏幕边缘
	 *   1.判断X轴上的位置
	 *     -MousePosition.X - ViewPort.X的绝对值大于 ViewPort - BorderLenght的值即为，鼠标到达边界
	 *   2.判断鼠标的方位
	 *     -第一步中计算的值若大于零，则鼠标在右边反之在左边
	 *    Y轴同理
	 *    在这里进行了一次坐标转换，以保证移动方向和三维默认场景方向一致
	 */
	float XDirection = MousePosition.X - ViewportCenterPoint.X;
	float YDirection = MousePosition.Y - ViewportCenterPoint.Y;
	if (abs(XDirection)>ViewportCenterPoint.X - BorderLength)
	{
		if (XDirection>0)
		{
			MoveDirection.Y = 1;
		}
		else
		{
			MoveDirection.Y = -1;
		}
	}

    if (abs(YDirection)>ViewportCenterPoint.Y - BorderLength)
    {
	    if (YDirection>0)
	    {
		    MoveDirection.X = -1;
	    }
	    else
	    {
		    MoveDirection.X = 1;
	    }
    }

	return MoveDirection;
}

// Called every frame
void ARTSObersver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetMovementComponent()->Velocity = 5000.f*CalculaterMoveDirection();

}

// Called to bind functionality to input
void ARTSObersver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

