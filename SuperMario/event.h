#pragma once

void MarioSlowEvent(class Mario*);
void MarioSpeedEvent(class Mario*);
void MarioTouchBorderEvent(class Mario* mario, class Camera* camera);
void EntityFallEvent(class Entity* entity);
void MarioJumpEvent(class Mario*);
void MarioSquatEvent(class Mario* mario);
void MarioUnSquatEvent(class Mario* mario);
void MarioEatPropEvent(class GameScene* gamescene, class Prop* prop);
void MarioOffInvincibilityEvent(class GameScene* gamescene);
void MarioShootFireballEvent(class GameScene* gamescene);
void FireballBoomEvent(class GameScene* gamescene, class Fireball* fireball, bool = true);
void MarioStompMonsterEvent(class GameScene* gamescene, class  Monster* monster);
void MarioDamageEvent(class GameScene* gamescene);
void MonsterHandstandEvent(class GameScene* gamescene, class  Monster* monster);
void MarioDeathEvent(class GameScene* gamescene);
void GameSceneReloadEvent(class GameScene* gamescene);
void MarioEnterPipeEvent(class GameScene* gamescene, class Pipe* pipe);
void MarioLeavePipeEvent(class GameScene* gamescene, class  Pipe* pipe);
void MarioTouchFlagEvent(class GameScene* gamescene);
void BlockStrikeEvent(class GameScene* gamescene, class Block* block, class  Mario* mario);