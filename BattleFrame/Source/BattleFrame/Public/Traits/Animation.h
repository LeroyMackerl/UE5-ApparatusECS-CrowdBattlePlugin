#pragma once
 
#include "CoreMinimal.h"
#include "AnimToTextureDataAsset.h"
#include "Animation.generated.h"
 
UENUM(BlueprintType)
enum class ESubjectState : uint8
{
    None UMETA(DisplayName = "None"),
    Dirty UMETA(DisplayName = "Dirty"),
    Appearing UMETA(DisplayName = "Appearing"),
    Idle UMETA(DisplayName = "Idle"),
    Moving UMETA(DisplayName = "Moving"),
    Attacking UMETA(DisplayName = "Attacking"),
    BeingHit UMETA(DisplayName = "BeingHit"),
    Dying UMETA(DisplayName = "Dying"),
    Falling UMETA(DisplayName = "Falling"),
    Jumping UMETA(DisplayName = "Jumping"),
    Sleeping UMETA(DisplayName = "Sleeping")
};

class ANiagaraSubjectRenderer;

USTRUCT(BlueprintType)
struct BATTLEFRAME_API FAnimation
{
	GENERATED_BODY()

private:

    mutable std::atomic<bool> LockFlag{ false };

public:

    void Lock() const
    {
        while (LockFlag.exchange(true, std::memory_order_acquire));
    }

    void Unlock() const
    {
        LockFlag.store(false, std::memory_order_release);
    }

    //-----------------------------------------------------------

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSoftObjectPtr <UAnimToTextureDataAsset> AnimToTextureDataAsset;

    UAnimToTextureDataAsset* AnimToTextureData;

    //-----------------------------------------------------------

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSubclassOf<ANiagaraSubjectRenderer> RendererClass;

    //-------------------------------------------------------------

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Tooltip = "动画间过度速度"))
    float LerpSpeed = 4;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Tooltip = "出生动画的索引值"))
    float IndexOfAppearAnim = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Tooltip = "攻击动画的索引值"))
    float IndexOfAttackAnim = 1;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Tooltip = "死亡动画的索引值"))
    float IndexOfDeathAnim = 2;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Tooltip = "待机动画的索引值"))
    float IndexOfIdleAnim = 3;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Tooltip = "移动动画的索引值"))
    float IndexOfMoveAnim = 4;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Tooltip = "高于此速度时切换到移动动画"))
    float UseMoveAnimAboveSpeed = 50.f;

    //-----------------------------------------------------------

    float AppearAnimLength = 1.f;
    float AttackAnimLength = 1.f;
    float DeathAnimLength = 1.f;

    //-----------------------------------------------------------

    float AnimIndex0 = IndexOfIdleAnim;
    float AnimPlayRate0 = 1.f;
    float AnimCurrentTime0 = 0.f;
    float AnimOffsetTime0 = 0.f;
    float AnimPauseTime0 = 0.f;

    float AnimIndex1 = IndexOfIdleAnim;
    float AnimPlayRate1 = 1.f;
    float AnimCurrentTime1 = 0.f;
    float AnimOffsetTime1 = 0.f;
    float AnimPauseTime1 = 0.f;

    float AnimLerp = 1;

    //-----------------------------------------------------------

    float HitGlow = 0;
    float FreezeFx = 0;
    float BurnFx = 0;
    float Dissolve = 1;

    //-----------------------------------------------------------

    ESubjectState SubjectState = ESubjectState::None;
    ESubjectState PreviousSubjectState = ESubjectState::Dirty;

    //-----------------------------------------------------------

    FAnimation() {};

    FAnimation(const FAnimation& Anim)
    {
        LockFlag.store(Anim.LockFlag.load());

        AnimToTextureDataAsset = Anim.AnimToTextureDataAsset;
        AnimToTextureData = Anim.AnimToTextureData;

        RendererClass = Anim.RendererClass;

        HitGlow = Anim.HitGlow;
        FreezeFx = Anim.FreezeFx;
        BurnFx = Anim.BurnFx;
        Dissolve = Anim.Dissolve;

        AnimIndex0 = Anim.AnimIndex0;
        AnimPlayRate0 = Anim.AnimPlayRate0;
        AnimCurrentTime0 = Anim.AnimCurrentTime0;
        AnimOffsetTime0 = Anim.AnimOffsetTime0;
        AnimPauseTime0 = Anim.AnimPauseTime0;

        AnimIndex1 = Anim.AnimIndex1;
        AnimPlayRate1 = Anim.AnimPlayRate1;
        AnimCurrentTime1 = Anim.AnimCurrentTime1;
        AnimOffsetTime1 = Anim.AnimOffsetTime1;
        AnimPauseTime1 = Anim.AnimPauseTime1;

        AnimLerp = Anim.AnimLerp;
        LerpSpeed = Anim.LerpSpeed;

        AppearAnimLength = Anim.AppearAnimLength;
        AttackAnimLength = Anim.AttackAnimLength;
        DeathAnimLength = Anim.DeathAnimLength;

        IndexOfAppearAnim = Anim.IndexOfAppearAnim;
        IndexOfIdleAnim = Anim.IndexOfIdleAnim;
        IndexOfMoveAnim = Anim.IndexOfMoveAnim;
        IndexOfAttackAnim = Anim.IndexOfAttackAnim;
        IndexOfDeathAnim = Anim.IndexOfDeathAnim;

        UseMoveAnimAboveSpeed = Anim.UseMoveAnimAboveSpeed;

        SubjectState = Anim.SubjectState;
        PreviousSubjectState = Anim.PreviousSubjectState;
    }

    FAnimation& operator=(const FAnimation& Anim)
    {
        LockFlag.store(Anim.LockFlag.load());

        AnimToTextureDataAsset = Anim.AnimToTextureDataAsset;
        AnimToTextureData = Anim.AnimToTextureData;

        RendererClass = Anim.RendererClass;

        HitGlow = Anim.HitGlow;
        FreezeFx = Anim.FreezeFx;
        BurnFx = Anim.BurnFx;
        Dissolve = Anim.Dissolve;

        AnimIndex0 = Anim.AnimIndex0;
        AnimPlayRate0 = Anim.AnimPlayRate0;
        AnimCurrentTime0 = Anim.AnimCurrentTime0;
        AnimOffsetTime0 = Anim.AnimOffsetTime0;
        AnimPauseTime0 = Anim.AnimPauseTime0;

        AnimIndex1 = Anim.AnimIndex1;
        AnimPlayRate1 = Anim.AnimPlayRate1;
        AnimCurrentTime1 = Anim.AnimCurrentTime1;
        AnimOffsetTime1 = Anim.AnimOffsetTime1;
        AnimPauseTime1 = Anim.AnimPauseTime1;

        AnimLerp = Anim.AnimLerp;
        LerpSpeed = Anim.LerpSpeed;

        AppearAnimLength = Anim.AppearAnimLength;
        AttackAnimLength = Anim.AttackAnimLength;
        DeathAnimLength = Anim.DeathAnimLength;

        IndexOfAppearAnim = Anim.IndexOfAppearAnim;
        IndexOfIdleAnim = Anim.IndexOfIdleAnim;
        IndexOfMoveAnim = Anim.IndexOfMoveAnim;
        IndexOfAttackAnim = Anim.IndexOfAttackAnim;
        IndexOfDeathAnim = Anim.IndexOfDeathAnim;

        UseMoveAnimAboveSpeed = Anim.UseMoveAnimAboveSpeed;

        SubjectState = Anim.SubjectState;
        PreviousSubjectState = Anim.PreviousSubjectState;

        return *this;
    }

};
