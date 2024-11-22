#pragma once
#include "OptionsItem.h"

// Ό³Έν :
class AOptionsList : public AActor
{
public:
	// constrcuter destructer
	AOptionsList();
	~AOptionsList();

	// delete Function
	AOptionsList(const AOptionsList& _Other) = delete;
	AOptionsList(AOptionsList&& _Other) noexcept = delete;
	AOptionsList& operator=(const AOptionsList& _Other) = delete;
	AOptionsList& operator=(AOptionsList&& _Other) noexcept = delete;

	inline void InitList() { CurIndex = 0; }
	void SetupList(float _ItemHeight, FVector2D _Offset);
	
	void AddItem(class AOptionsItem* _Item)
	{
		ItemList.push_back(_Item);
	}

	void SetActive(bool _Value)override
	{
		UObject::SetActive(_Value);
		Title->SetActive(_Value);
		for (auto Item : ItemList)
		{
			Item->SetActive(_Value);
		}
	}

	inline AOptionsItem* GetSelectedItem()
	{
		return ItemList[CurIndex];
	}
	
	inline void Execute()
	{
		ItemList[CurIndex]->Select();
	}

	inline void PrevItem()
	{
		if (CurIndex - 1 >= 0)
		{
			CurIndex--;
		}
	}

	inline void NextItem()
	{
		if (CurIndex + 1 < ItemList.size())
		{
			CurIndex++;
		}
	}

	inline void SetItemTitle(AOptionsItem* _Title, FVector2D _TitlePos)
	{
		Title = _Title;
		TitlePos = _TitlePos;
	}

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	int CurIndex = 0;
	float ItemHeight = 0;
	FVector2D Offset;
	FVector2D TitlePos;
	//AOptionsManager Manager;
	AOptionsItem* Title;
	std::vector<AOptionsItem*> ItemList;
	//std::list<AOptionsItem*>::iterator InnerItr;
};

