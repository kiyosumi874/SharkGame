#pragma once
#include <vector>
#include <functional>
#include "GameStateBase.h"
#include "GameStateType.h"
#include "GameStateInitializeData.h"


/// <summary>
/// �Q�[���X�e�[�g���܂Ƃ߂��N���X
/// </summary>
class GameStates
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameStates(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GameStates();

    /// <summary>
    /// �X�e�[�g���擾����
    /// </summary>
    /// <param name="type">�X�e�[�g�̎��</param>
    /// <returns>�X�e�[�g�̃C���X�^���X</returns>
    GameStateBase* GetState(const GameStateType type);
private:
    class GameStateTitle* gameStateTitle;
    class GameStateStartCountDown* gameStateStartCountDown;
    class GameStatePlayerRound* gameStatePlayerRound;
    class GameStateSharkShoot* gameStateSharkShoot;
    class GameStateSharkFly* gameStateSharkFly;
    class GameStateSharkLandsOnWater* gameStateSharkLandsOnWater;
    class GameStateResult* gameStateResult;

    std::vector<GameStateBase*> gameStates;
};