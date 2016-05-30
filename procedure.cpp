#include <cmath>
#include <math.h>
#include "procedure.h"

//信息文件中储存  attackRangeDegree, attackTimeGap
void ATjudgement::judgement_add_dogface(ATdogface new_dogface){
	dogface_information.push_back(new_dogface);
}

void ATjudgement::judgement_add_attack(ATattack new_attack){
	ATattackAndTime new_attackAndTime;
	new_attackAndTime.ATattack = new_attack;
	new_attackAndTime.timeRemained = new_attack.attack_get_duration();/////////
	attack_information.push_back(new_attackAndTime);         
}

void ATjudgement::judgement_attacks_impdamage(std::list<ATattack>::iterator attackIter, std::list<ATcharacter>::iterator charaIter){
	std::list<ATattack>::iterator i = attackIter;
	std::list<ATcharacter>::iterator j = charaIter;
	int damage = (*i).element_get_damage();
	///////////attack_get_buff??
	///unit_be _hurt只是hp减,没有
	int* attackBuff = (*i).attack_get_buff();
	if()

	if()
		(*j).unit_be_hurt(damage, slower);
	if((*i).attack_get_buff = blood)
		(*j).unit_be_hurt(damage, blood);
	if((*i).attack_get_buff = stun){
		(*j).unit_be_hurt(damage, stun);
		(*j).hero_change_attack_speed();
	}
	if((*i).attack_get_buff = burn)
		(*j).unit_be_hurt(damage, burn);
}
//远程是碰到人（我）或者碰到墙消失，近程有个时间，每次需要减，攻击时间到，去除（我）
///有一个持续时间，如果时间到了就结束 
void ATjudgement::judgement_attacks(){
	for(auto i = attack_information.begin(); i != attack_information.end(); ){
		if(i == character_information.end()){
			i = dogface_information.begin();
		}
		while((*i).timeRemained == 0){
			attack_information.erase(i);
			if(attack_information.empty())
				break;
		}
		int hitflg = 0;
		for(auto j = character_information.begin(); j != character_information.end(); ++j){
			// character judgement first. Followed by dogface judgement.
			if((*i).owner != (*j).element_ID){
				int* posAttack = (*i).element_get_position();
				int* posCharacter = (*j).element_get_position();
				double distance = std::sqrt(std::pow(posAttack[0] - posCharacter[0], 2.0) + std::pow(posAttack[1] - posCharacter[1], 2.0));
				if( (posCharacter[0] - posAttack[0]) >= 0 )
					double dirAttackUnit = std::atan((posCharacter[0] - posAttack[0])/(posCharacter[1] - posAttack[1]));
				else{
					if( (posCharacter[1] - posAttack[1]) >= 0 )
						double dirAttackUnit = Pi/2 + std::atan((posCharacter[0] - posAttack[0])/(posCharacter[1] - posAttack[1]));
					else
						double dirAttackUnit = (-1)*Pi/2 + std::atan((posCharacter[0] - posAttack[0])/(posCharacter[1] - posAttack[1]));
				}
				double attackDir = (*i).element_get_direction();
				double dirStart = attackDir - attackRangeDegree;
				double dirEnd = attackDir + attackRangeDegree;
				int attackRange = /////
				int unitSize = /////
				double extradir = std::asin(unitSize / distance);
				if( (dirStart < dirAttackUnit)&&(dirAttackUnit < dirEnd) ){
					if(distance < (attackRange + unitSize)){
						judgement_attacks_impdamage(i, j);
						attack_information.erase(i);
						hitflg = 1;
						break;
					}
				}else if( (dirAttackUnit > dirEnd)&&(dirAttackUnit < (extradir + dirEnd)) ){
					double k0 = std::tan(dirEnd);
					double k1 = -1 / k0;
					double crossX = ( posCharacter[1] - posAttack[1] - k1 * posCharacter[0] + k0 * posAttack[0] ) / (k0 - k1);
					double crossY = k0 * crossX + posAttack[1] - k0 * posAttack[0];
					double distance2cross = std::sqrt( std::pow((crossX - posAttack[0]), 2.0) + std::pow((crossY - posAttack[1]), 2.0) );
					if(distance < std::sqrt( std::pow(unitSize, 2.0) + std::pow(distance2cross, 2.0) )){
						judgement_attacks_impdamage(i, j);
						attack_information.erase(i);
						hitflg = 1;
						break;
					}
				}else if( (dirAttackUnit < dirStart)&&(dirAttackUnit > (dirStart - extradir)) ){
					double k0 = std::tan(dirStart);
					double k1 = -1 / k0;
					double crossX = ( posCharacter[1] - posAttack[1] - k1 * posCharacter[0] + k0 * posAttack[0] ) / (k0 - k1);
					double crossY = k0 * crossX + posAttack[1] - k0 * posAttack[0];
					double distance2cross = std::sqrt( std::pow((crossX - posAttack[0]), 2.0) + std::pow((crossY - posAttack[1]), 2.0) );
					if(distance < std::sqrt( std::pow(unitSize, 2.0) + std::pow(distance2cross, 2.0) )){
						judgement_attacks_impdamage(i, j);
						attack_information.erase(i);
						hitflg = 1;
						break;
					}
				}
			}else{
				continue;
			}
			if(hitflg == 0){
				if((*i).attack.attak_get_type() == melee)///////////
					(*i).timeRemained -= attackTimeGap;
			}
		}
	}
	
}

void ATjudgement::judgement_check_state(){
	for(auto i = dogface_information.begin(); i != dogface_information.end(); ++i){
		///////返回值？
		(*i).unit_check_state();
	}
	for(auto i = character_information.begin(); i != character_information.end(); ++i)
		////同上
		(*i).unit_check_state();
}