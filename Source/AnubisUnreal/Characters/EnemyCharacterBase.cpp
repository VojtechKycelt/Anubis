// Made by sir Wok for AnubisUnreal project


#include "EnemyCharacterBase.h"

#include "AnubisUnreal/Macros.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemyCharacterBase::AEnemyCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("AttributeSet"));

}

void AEnemyCharacterBase::GiveDefaultAbilities()
{
	check(AbilitySystemComponent);

	for (TSubclassOf<UGameplayAbility> Ability : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(Ability,1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void AEnemyCharacterBase::InitDefaultAttributes()
{
	if (!AbilitySystemComponent || !DefaultAttributeEffect) return;

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect,1.f, EffectContextHandle);

	if (EffectSpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		AttributeSet->bAttributesInitialized = true;
	}

	
}
void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
	InitDefaultAttributes();
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AIController = Cast<AAIController>(GetController());
}

void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AttributeSet->GetHealth() <= 0 && !bIsDead)
	{
		bIsDead = true;
		MyDeathEvent();
	}
}


