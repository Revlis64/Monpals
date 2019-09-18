//By Revlis, released 12th of September, 2019
//
//  Copyright (C) 2019 Revlis
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

// Modified by Pharap

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <EEPROM.h>

#include "Images.h"
#include "Sounds.h"

Arduboy2 arduboy;
BeepPin2 beep;

ArduboyTones sound(arduboy.audio.enabled);

//Variables, Structures, etc.

struct Monpals
{
	uint8_t mons[6][2];
	uint8_t player;
	uint8_t enemy;
	uint8_t attacker;
	uint8_t victim;
	uint8_t type[6];
	uint8_t spc[6];
	uint8_t lvl[6];
	uint8_t maxHlt[6];
	uint8_t hlt[6];
	uint8_t maxEng[6];
	uint8_t eng[6];
	uint8_t atk[6];
	uint8_t def[6];
	uint8_t spd[6];
	uint8_t cdn[6];
};

Monpals monpals;

short i;
short dmg;
short c;
uint8_t rnd;
uint8_t engCost;
uint8_t a;
uint8_t b;
uint8_t t;
uint8_t menuCursor;
uint8_t buttonClick;
uint8_t GameState;
uint8_t boxedMons[15][2];
uint8_t items;
uint8_t herb;
uint8_t coffee;
uint8_t cure;
uint8_t revive;
uint8_t gold;
uint8_t itemChoice;
uint8_t medals;
int8_t goldEarnings;
bool battleStart;
bool victory;
bool arenaBattle;
bool flicker;

/////////////////////////////////////////////////////////////////////////////////////////////

//Fuctions

void MonConstruct()
{
	MonClearConstruct();

	for (i = 3; i <= 5; ++i)
	{
		monpals.mons[i][0] = 0;
		monpals.mons[i][1] = 0;
	}

	EnemyMonConstruct();


	for (a = 0; a <= 5; ++a)
	{
		MonLvlSpcConstruct();

		i = monpals.mons[a][1];
		MonStatConstruct();

		MonSpcStatConstruct();

		monpals.maxHlt[a] = (((monpals.def[a] + monpals.maxEng[a]) / 2) + 1) * monpals.lvl[a];
		monpals.hlt[a] = monpals.maxHlt[a];
		monpals.maxEng[a] *= 2;
		monpals.eng[a] = monpals.maxEng[a];
	}

	ItemConstruct();

	victory = false;
	battleStart = false;
	goldEarnings = 0;
	monpals.player = 0;
	monpals.enemy = 3;
	GameState = 1;
}

void BattleVisuals()
{
	arduboy.clear();
	for (b=0;b <= 1;++b)
	{
		if (b == 0) a = monpals.player;
		if (b == 1) a = monpals.enemy;

		arduboy.setTextColor(WHITE);
		arduboy.setTextBackground(BLACK);

		if (monpals.hlt[a] > 0)
		{
			if (b == 0)
				arduboy.setCursor(32, 32);

			if (b == 1)
				arduboy.setCursor(0, 8);

			t = monpals.mons[a][0];
			Text();

			if (monpals.spc[a] == 1)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, audiouseBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, audiouseFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 2)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, beethroneBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, beethroneFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 3)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, bubblueBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, bubblueFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 4)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, bunnerinaBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, bunnerinaFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 5)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, chlorosaurBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, chlorosaurFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 6)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, kribbitBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, kribbitFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 7)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, micruntBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, micruntFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 8)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, okardBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, okardFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 9)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, pecawBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, pecawFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 10)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, poltergrabBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, poltergrabFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 11)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, serpurntBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, serpurntFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 12)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, slugammaBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, slugammaFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 13)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, spymeraBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, spymeraFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 14)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, squeamaskBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, squeamaskFront, 24, 24, WHITE);
			}

			if (monpals.spc[a] == 15)
			{
				if (b == 0)
					arduboy.drawBitmap(0, 24, xenaucerBack, 24, 24, WHITE);

				if (b == 1)
					arduboy.drawBitmap(104, 0, xenaucerFront, 24, 24, WHITE);
			}

			if (b == 0)
				arduboy.setCursor(32, 24);

			if (b == 1)
				arduboy.setCursor(0, 0);

			if (monpals.cdn[a] == 1)
				arduboy.print("WOUNDED");

			if (monpals.cdn[a] == 2)
				arduboy.print("DAZED");

			if (monpals.cdn[a] == 3)
				arduboy.print("ASLEEP");

			if (b == 0)
				arduboy.setCursor(98, 32);

			if (b == 1)
				arduboy.setCursor(66, 8);

			arduboy.print(F("LVL"));
			arduboy.print(monpals.lvl[a]);

			if (b == 0)
				arduboy.setCursor(32, 40);

			if (b == 1)
				arduboy.setCursor(0, 16);

			arduboy.print(F("H"));
			arduboy.print(monpals.hlt[a]);
			arduboy.print(F("/"));
			arduboy.print(monpals.maxHlt[a]);

			if (b == 0)
				arduboy.setCursor(92, 40);

			if (b == 1)
				arduboy.setCursor(60, 16);

			arduboy.print(F("E"));
			arduboy.print(monpals.eng[a]);
			arduboy.print(F("/"));
			arduboy.print(monpals.maxEng[a]);
		}

		arduboy.fillRect(0, 48, 128, 16, WHITE);
		arduboy.setTextColor(BLACK);
		arduboy.setTextBackground(WHITE);
	}
}

void BattleMenuVisuals()
{
	if (buttonClick == 0)
	{
		engCost = monpals.maxEng[monpals.player]/monpals.spd[monpals.player];

		if (engCost < 1)
			engCost = 1;

		arduboy.setCursor(0, 48);
		arduboy.print(F("What will you do?"));
		arduboy.setCursor(0, 56);

		if(menuCursor == 0)
		{
			arduboy.print(F("<ATTACK >"));
			arduboy.print(F("-"));
			arduboy.print(engCost);
			arduboy.print(F("ENG"));
		}
		else if(menuCursor == 1)
		{
			arduboy.print(F("<DEFEND >"));
			arduboy.print(F("-"));
			arduboy.print(engCost);
			arduboy.print(F("ENG"));
		}
		else if(menuCursor == 2)
		{
			arduboy.print(F("<ITEMS  >"));
		}
		else if(menuCursor == 3)
		{
			arduboy.print(F("<SWITCH >"));
		};
	}

	if (buttonClick == 1)
	{
		arduboy.setCursor(0, 48);
		arduboy.print(F("Which item?"));
		arduboy.setCursor(0, 56);

		if(menuCursor == 0)
		{
			arduboy.print(F("<HERB   >x"));
			arduboy.print(herb);
		}
		else if(menuCursor == 1)
		{
			arduboy.print(F("<COFFEE >x"));
			arduboy.print(coffee);
		}
		else if(menuCursor == 2)
		{
			arduboy.print(F("<CURE   >x"));
			arduboy.print(cure);
		}
		else if(menuCursor == 3)
		{
			arduboy.print(F("<REVIVE >x"));
			arduboy.print(revive);
		}
	}

	if (buttonClick > 1)
	{
		MonpalSelection();
	};

	if (buttonClick != 0)
	{
		arduboy.setCursor(84, 56);
		arduboy.print(F("(A)BACK"));
	};
}

void BattleConditionVisuals()
{
	BattleVisuals();

	t = monpals.mons[monpals.attacker][0];

	arduboy.setCursor(0, 48);
	if (monpals.attacker == monpals.enemy)
		arduboy.print(F("Foe "));

	Text();
}

void BattleCondition()
{
	rnd = random(1, 101);

	if (monpals.cdn[monpals.attacker] == 2)
	{
		if (rnd <= 50)
		{
			dmg = monpals.atk[monpals.attacker] * ((monpals.lvl[monpals.attacker] / ((monpals.def[monpals.attacker] + ((monpals.lvl[monpals.attacker] / 3) + 1)) / 2)) + 1);

			if (dmg <= 0)
				dmg = 1;

			if (dmg >= monpals.hlt[monpals.attacker])
				monpals.hlt[monpals.attacker] = 0;
			else monpals.hlt[monpals.attacker]
				-= dmg;

			monpals.eng[monpals.attacker] -= engCost;

			BattleConditionVisuals();
			arduboy.print(F(" hurt itself in its daze."));
		}
		else
		{
			monpals.cdn[monpals.attacker] = 0;
			BattleConditionVisuals();
			arduboy.print(F(" snapped out of its daze."));
		};

		arduboy.display();
		delay(2000);
	};

	if (monpals.cdn[monpals.attacker] == 3)
	{
		if (rnd <= 50)
		{
			BattleConditionVisuals();
			arduboy.print(F(" is fast asleep."));
		}
		else
		{
			monpals.cdn[monpals.attacker] = 0;
			monpals.eng[monpals.attacker] = monpals.maxEng[monpals.attacker];
			BattleConditionVisuals();
			arduboy.print(F(" woke up."));
		}

		arduboy.display();
		delay(2000);
	};

	if (monpals.eng[monpals.attacker] < engCost and monpals.eng[monpals.attacker] > 0)
	{
		monpals.eng[monpals.attacker] = 0;
		BattleConditionVisuals();
		arduboy.print(F(" needs more energy to use."));
		arduboy.display();
		delay(2000);
		BattleSleep();
	};
}

void BattleAttack()
{
	BattleCondition();
	dmg = monpals.atk[monpals.attacker] * ((monpals.lvl[monpals.attacker] / ((monpals.def[monpals.victim] + ((monpals.lvl[monpals.victim] / 3) + 1)) / 2)) + 1);

	if (monpals.cdn[monpals.attacker] == 1)
		dmg /= 2;

	if (monpals.cdn[monpals.victim] == 1)
		dmg *= 2;

	rnd = random(1, 101);

	if (monpals.eng[monpals.attacker] >= engCost and monpals.cdn[monpals.attacker] != 2 and monpals.cdn[monpals.attacker] != 3)
	{
		if (rnd <= 10)
		{
			monpals.eng[monpals.attacker] -= engCost;
			BattleVisuals();

			t = monpals.mons[monpals.attacker][0];
			arduboy.setCursor(0, 48);

			if (monpals.attacker == monpals.enemy) arduboy.print(F("Foe "));

			Text();

			arduboy.print(F(" missed."));
			arduboy.display();
			delay(2000);
		}
		else if (rnd >= 11 and rnd <= 100 and monpals.cdn[monpals.attacker] != 2 and monpals.cdn[monpals.attacker] != 3)
		{
			monpals.eng[monpals.attacker] -= engCost;
			BattleVisuals();
			arduboy.display();

			if (rnd <= 15)
			{
				a = 8;
				dmg *= 2;
			}
			else
				a = 4;

			beep.tone(beep.freq(25));
			delay(67);
			beep.tone(beep.freq(50));
			delay(67);
			beep.noTone();

			for (b = 1; b <= a; b++)
			{
				if (flicker == true)
					flicker = false;
				else
					flicker = true;

				Arduboy2::invert(flicker);
				delay(400 / a);
			};

			Arduboy2::invert(false);
			flicker = false;
			if (rnd <= 15)
			{
				arduboy.setCursor(0, 48);
				arduboy.print(F("CRITICAL HIT!"));
				arduboy.display();
				delay(2000);
			};

			BattleVisuals();

			if ((monpals.type[monpals.attacker] == 1 and monpals.type[monpals.victim] == 2) or (monpals.type[monpals.attacker] == 2 and monpals.type[monpals.victim] == 3) or (monpals.type[monpals.attacker] == 3 and monpals.type[monpals.victim] == 1))
			{
				dmg *= 2;
				if (dmg < 2) dmg = 2;
				arduboy.setCursor(0, 48);
				arduboy.print(F("SUPER EFFECTIVE!"));
				arduboy.display();
				delay(2000);
			}
			else if ((monpals.type[monpals.attacker] == 1 and monpals.type[monpals.victim] == 3) or (monpals.type[monpals.attacker] == 2 and monpals.type[monpals.victim] == 1) or (monpals.type[monpals.attacker] == 3 and monpals.type[monpals.victim] == 2))
			{
				dmg /= 2;
				arduboy.setCursor(0, 48);
				arduboy.print(F("Not very effective."));
				arduboy.display();
				delay(2000);
			};

			if (rnd <= 15)
			{
				if (dmg < 2) dmg = 2;
			}
			else
			{
				if (dmg <= 0) dmg = 1;
			}

			if (dmg >= monpals.hlt[monpals.victim])
				monpals.hlt[monpals.victim] = 0;
			else
				monpals.hlt[monpals.victim] -= dmg;

			BattleVisuals();
			t = monpals.mons[monpals.attacker][0];
			arduboy.setCursor(0, 48);

			if (monpals.attacker == monpals.enemy)
				arduboy.print(F("Foe "));
			Text();

			arduboy.print(F(" did "));
			arduboy.setCursor(0, 56);
			arduboy.print(dmg);
			arduboy.print(F(" damage."));
			arduboy.display();
			delay(2000);

			rnd = random(1, 101);

			if (rnd >= 1 and rnd <= 2 and monpals.cdn[monpals.victim] == 0 and monpals.hlt[monpals.victim] > 0)
			{
				monpals.cdn[monpals.victim] = 2;

				BattleVisuals();

				t = monpals.mons[monpals.victim][0];
				arduboy.setCursor(0, 48);

				if (monpals.attacker == monpals.player)
					arduboy.print(F("Foe "));

				Text();

				arduboy.print(F(" is dazed."));
				arduboy.display();
				delay(2000);
			}

			if (rnd >= 99 and rnd <= 100 and monpals.cdn[monpals.victim] == 0 and monpals.hlt[monpals.victim] > 0)
			{
				monpals.cdn[monpals.victim] = 1;

				BattleVisuals();

				t = monpals.mons[monpals.victim][0];
				arduboy.setCursor(0, 48);

				if (monpals.attacker == monpals.player)
					arduboy.print(F("Foe "));

				Text();

				arduboy.print(F(" is wounded."));
				arduboy.display();
				delay(2000);
			}
		}
	}

	BattleSleep();
}

void BattleSleep()
{
	if (monpals.eng[monpals.attacker] == 0 and monpals.cdn[monpals.attacker] != 3 and monpals.hlt[monpals.attacker] != 0)
	{
		monpals.cdn[monpals.attacker] = 3;

		BattleVisuals();

		t = monpals.mons[monpals.attacker][0];
		arduboy.setCursor(0, 48);

		if (monpals.attacker == monpals.enemy)
		 arduboy.print(F("Foe "));

		Text();

		arduboy.print(F(" fell asleep."));
		arduboy.display();
		delay(2000);
	}
}

void BattleDefense()
{
	BattleCondition();
	if (monpals.eng[monpals.attacker] >= engCost and monpals.cdn[monpals.attacker] != 2 and monpals.cdn[monpals.attacker] != 3)
	{
		rnd = random(2, 5);
		monpals.eng[monpals.attacker] -= engCost;

		if ((monpals.def[monpals.attacker]+rnd) >= 10)
		{
			monpals.def[monpals.attacker] = 10;

			BattleVisuals();

			t = monpals.mons[monpals.attacker][0];
			arduboy.setCursor(0, 48);

			Text();

			arduboy.print(F("'s defense reached its limit."));
			arduboy.display();
			delay(2000);
		}
		else
		{
			monpals.def[monpals.attacker] += rnd;

			BattleVisuals();

			t = monpals.mons[monpals.attacker][0];
			arduboy.setCursor(0, 48);

			Text();

			arduboy.print(F("'s defense went up."));
			arduboy.display();
			delay(2000);

			BattleSleep();
		}
	}
}



void BattleItemMissUsed()
{
	BattleVisuals();

	arduboy.setCursor(0, 48);
	arduboy.print(F("Improper use of item."));
	arduboy.display();
	delay(2000);
	i = 2;
}



void BattleHerb()
{
	if ((monpals.spd[monpals.player] * monpals.lvl[monpals.player]) >= (monpals.spd[monpals.enemy] * monpals.lvl[monpals.enemy]))
		i = 1;
	else
		i = 0;

	if (monpals.hlt[menuCursor] == monpals.maxHlt[menuCursor] or monpals.hlt[menuCursor] == 0)
	{
		BattleItemMissUsed();
	}
	else
	{
		rnd = random((monpals.maxHlt[menuCursor]/2), monpals.maxHlt[menuCursor]);

		if (rnd >= (monpals.maxHlt[menuCursor] - monpals.hlt[menuCursor]))
			monpals.hlt[menuCursor] = monpals.maxHlt[menuCursor];
		else
			monpals.hlt[menuCursor] = rnd;

		BattleVisuals();

		t = monpals.mons[menuCursor][0];
		arduboy.setCursor(0, 48);

		Text();

		arduboy.print(F(" healed some health."));
		arduboy.display();
		delay(2000);

		--herb;
	};
}

void BattleCoffee()
{
	if ((monpals.spd[monpals.player] * monpals.lvl[monpals.player]) >= (monpals.spd[monpals.enemy] * monpals.lvl[monpals.enemy]))
		i = 1;
	else
		i = 0;

	if (monpals.eng[menuCursor] == monpals.maxEng[menuCursor] or monpals.hlt[menuCursor] == 0)
	{
		BattleItemMissUsed();
	}
	else
	{
		monpals.eng[menuCursor] = monpals.maxEng[menuCursor];

		if (monpals.cdn[menuCursor] == 3)
			monpals.cdn[menuCursor] = 0;

		BattleVisuals();

		t = monpals.mons[menuCursor][0];
		arduboy.setCursor(0, 48);

		Text();

		arduboy.print(F(" gained some energy."));
		arduboy.display();
		delay(2000);

		--coffee;
	}
}

void BattleCure()
{
	if ((monpals.spd[monpals.player] * monpals.lvl[monpals.player]) >= (monpals.spd[monpals.enemy] * monpals.lvl[monpals.enemy]))
		i = 1;
	else
		i = 0;

	if (monpals.cdn[menuCursor] == 0 or monpals.hlt[menuCursor] == 0)
	{
		BattleItemMissUsed();
	}
	else
	{
		if (monpals.cdn[menuCursor] == 3)
			monpals.eng[menuCursor]=monpals.maxEng[menuCursor];

		monpals.cdn[menuCursor] = 0;

		BattleVisuals();

		t = monpals.mons[menuCursor][0];
		arduboy.setCursor(0, 48);

		Text();

		arduboy.print(F(" has been cured."));
		arduboy.display();
		delay(2000);

		--cure;
	};
}

void BattleRevive()
{
	if ((monpals.spd[monpals.player] * monpals.lvl[monpals.player]) >= (monpals.spd[monpals.enemy] * monpals.lvl[monpals.enemy]))
		i = 1;
	else
		i = 0;

	if (monpals.hlt[menuCursor] > 0 or monpals.spc[menuCursor] == 0)
	{
		BattleItemMissUsed();
	}
	else
	{
		monpals.cdn[menuCursor] = 0;
		monpals.hlt[menuCursor] = monpals.maxHlt[menuCursor] / 2;
		monpals.eng[menuCursor] = monpals.maxEng[menuCursor];

		BattleVisuals();

		t = monpals.mons[menuCursor][0];
		arduboy.setCursor(0, 48);

		Text();

		arduboy.print(F(" is revived."));
		arduboy.display();
		delay(2000);

		--revive;
	};
}

void BattleFinale()
{
	if (victory == true)
	{
		BattleVisuals();
		arduboy.setCursor(0, 48);

		if (arenaBattle == true)
		{
			arduboy.print(F("The champion is defeated."));
			++medals;
		}
		else
			arduboy.print(F("Your opponent is defeated."));

		arduboy.display();
		delay(2000);

		goldEarnings = ((monpals.lvl[3] + monpals.lvl[4] + monpals.lvl[5]) / 3) + 1;

		if (arenaBattle == true)
			goldEarnings *= (medals + 1);

		if ((255 - (gold + goldEarnings)) <= 0)
		{
			gold = 255;
			BattleVisuals();
			arduboy.setCursor(0, 48);
			arduboy.print(F("Your gold is full!"));
			arduboy.display();
			delay(2000);
		}
		else
		{
			BattleVisuals();
			gold += goldEarnings;
			arduboy.setCursor(0, 48);
			arduboy.print(F("You've earned "));
			arduboy.print(goldEarnings);
			arduboy.print(F(" gold."));
			arduboy.display();
			delay(2000);
		}
	}
	else
	{
		BattleVisuals();
		arduboy.setCursor(0, 48);
		arduboy.print(F("You've been defeated."));
		arduboy.display();
		delay(2000);
	}

	sound.noTone();
	GameState = 2;
	arenaBattle = false;

	items = 0;

	for (herb; herb > 0; --herb)
	{
		items += 64;
	}

	for (coffee; coffee > 0; --coffee)
	{
		items += 16;
	}

	for (cure; cure > 0; --cure)
	{
		items += 4;
	}

	for (revive; revive > 0; --revive)
	{
		++items;
	}
}

void BattleSwitch()
{
	if (buttonClick == 2)
	{
		if (menuCursor == monpals.player)
		{
			i = 2;
			BattleVisuals();
			arduboy.setCursor(0, 48);
			arduboy.print(F("This monpal is already out."));
			arduboy.display();
			delay(2000);
		}
		else if (monpals.spc[menuCursor] == 0)
		{
			i = 2;
			BattleVisuals();
			arduboy.setCursor(0, 48);
			arduboy.print(F("No monpal here."));
			arduboy.display();
			delay(2000);
		}
		else if (monpals.hlt[menuCursor] == 0)
		{
			i = 2;
			BattleVisuals();
			arduboy.setCursor(0, 48);
			arduboy.print(F("This monpal is KOed."));
			arduboy.display();
			delay(2000);
		}
		else
		{
			monpals.player = menuCursor;

			if ((monpals.spd[monpals.player] * monpals.lvl[monpals.player]) >= (monpals.spd[monpals.enemy] * monpals.lvl[monpals.enemy]))
				i = 1;
			else
				i = 0;

			BattleVisuals();

			t = monpals.mons[monpals.player][0];
			arduboy.setCursor(0, 48);
			arduboy.print(F("You switched to "));

			Text();

			arduboy.print(F("."));
			arduboy.display();
			delay(2000);
		}
	}
}

void BattleSendOut()
{
	if (buttonClick == 4)
	{
		if (monpals.spc[menuCursor] == 0)
		{
			i = 2;

			BattleVisuals();

			arduboy.setCursor(0, 48);
			arduboy.print(F("No monpal here."));
			arduboy.display();
			delay(2000);
		}
		else if (monpals.hlt[menuCursor] == 0)
		{
			i = 2;

			BattleVisuals();

			arduboy.setCursor(0, 48);
			arduboy.print(F("This monpal is KOed."));
			arduboy.display();
			delay(2000);
		}
		else
		{
			monpals.player = menuCursor;
			t = monpals.spc[menuCursor];
			i = 2;

			BattleVisuals();

			t = monpals.mons[monpals.player][0];
			arduboy.setCursor(0, 48);
			arduboy.print(F("You sent out "));

			Text();

			arduboy.print(F("."));
			arduboy.display();
			delay(2000);

			buttonClick = 0;
			menuCursor = 0;
		}
	}
}

void Battle()
{
	if (battleStart == false)
	{
		battleStart = true;
		sound.tones(battleMusic);
		BattleVisuals();
		arduboy.setCursor(0, 48);
		arduboy.print(F("Let the battle begin!"));
		arduboy.display();
		delay(2000);
	}

	if(arduboy.justPressed(LEFT_BUTTON) and menuCursor > 0)
	{
		beep.tone(beep.freq(500), 1);
		--menuCursor;
	}

	if(arduboy.justPressed(RIGHT_BUTTON) and menuCursor < 3)
	{
		if (menuCursor >= 2 and (buttonClick > 1))
			menuCursor = 2;
		else
		{
			beep.tone(beep.freq(500), 1);
			++menuCursor;
		}
	}

	if(arduboy.justPressed(A_BUTTON) and buttonClick > 0 and buttonClick < 4)
	{
		beep.tone(beep.freq(500), 1);

		if (buttonClick == 3)
			buttonClick = 1;
		else
			buttonClick = 0;

		menuCursor = 0;
	}

	if(arduboy.justPressed(B_BUTTON))
	{
		beep.tone(beep.freq(500));
		delay(67);
		beep.noTone();

		for (i = 0; i <= 1; ++i)
		{
			if ((monpals.hlt[monpals.player] <= 0) or (monpals.hlt[monpals.enemy] <= 0))
				i = 2;

			BattleSendOut();

			if (buttonClick == 3)
			{
				if (itemChoice == 1)
					BattleHerb();

				if (itemChoice == 2)
					BattleCoffee();

				if (itemChoice == 3)
					BattleCure();

				if (itemChoice == 4)
					BattleRevive();
			}

			if (buttonClick == 1)
			{
				if (menuCursor == 0 and herb > 0)
				{
					itemChoice = 1;
					menuCursor = 0;
					buttonClick = 3;
					i = 2;
				}
				else if (menuCursor == 1 and coffee > 0)
				{
					itemChoice = 2;
					menuCursor = 0;
					buttonClick = 3;
					i = 2;
				}
				else if (menuCursor == 2 and cure > 0)
				{
					itemChoice = 3;
					menuCursor = 0;
					buttonClick = 3;
					i = 2;
				}
				else if (menuCursor == 3 and revive > 0)
				{
					itemChoice = 4;
					menuCursor = 0;
					buttonClick = 3;
					i = 2;
				}
				else
				{
					i = 2;
					BattleVisuals();
					arduboy.setCursor(0, 48);
					arduboy.print(F("Not enough."));
					arduboy.display();
					delay(2000);
				}
			}

			if (menuCursor == 2 and buttonClick == 0)
			{
				menuCursor = 0;
				buttonClick = 1;
				i = 2;
			};

			BattleSwitch();

			if (menuCursor == 3 and buttonClick == 0)
			{
				i = 2;
				buttonClick = 2;
				menuCursor = 0;
			};

			if ((((monpals.spd[monpals.player] * monpals.lvl[monpals.player]) >= (monpals.spd[monpals.enemy] * monpals.lvl[monpals.enemy]) and i == 0) or ((monpals.spd[monpals.player] * monpals.lvl[monpals.player]) < (monpals.spd[monpals.enemy] * monpals.lvl[monpals.enemy]) and i == 1)) and buttonClick == 0)
			{
				monpals.attacker = monpals.player;
				monpals.victim = monpals.enemy;
				engCost=monpals.maxEng[monpals.player] / monpals.spd[monpals.player];

				if (engCost < 1)
					engCost = 1;

				if (menuCursor == 0)
					BattleAttack();

				if (menuCursor == 1)
					BattleDefense();
			}

			if (((monpals.spd[monpals.player]*monpals.lvl[monpals.player]) < (monpals.spd[monpals.enemy]*monpals.lvl[monpals.enemy]) and i == 0) or ((monpals.spd[monpals.player]*monpals.lvl[monpals.player]) >= (monpals.spd[monpals.enemy]*monpals.lvl[monpals.enemy]) and i == 1))
			{
				monpals.attacker = monpals.enemy;
				monpals.victim = monpals.player;
				engCost = monpals.maxEng[monpals.enemy] / monpals.spd[monpals.enemy];

				if (buttonClick != 0)
				{
					i = 2;
					buttonClick = 0;
					menuCursor = 0;
				}

				if (engCost < 1)
					engCost = 1;

				BattleAttack();
			}

			if ((monpals.hlt[monpals.player] <= 0) or (monpals.hlt[monpals.enemy] <= 0))
				i = 1;

			if (monpals.hlt[monpals.enemy] <= 0 and (monpals.hlt[4] > 0 or monpals.hlt[5] > 0) and monpals.enemy != 5)
			{
				BattleVisuals();
				t = monpals.spc[monpals.enemy];

				arduboy.setCursor(0, 48);
				arduboy.print(F("Foe "));

				Text();

				arduboy.print(F(" was defeated."));
				arduboy.display();
				delay(2000);

				++monpals.enemy;

				BattleVisuals();

				t=monpals.spc[monpals.enemy];
				arduboy.setCursor(0, 48);
				arduboy.print(F("Opponent sent out "));

				Text();

				arduboy.print(F("."));
				arduboy.display();
				delay(2000);
			}
			else if (monpals.hlt[3] == 0 and monpals.hlt[4] == 0 and monpals.hlt[5] == 0)
			{
				victory = true;
				BattleFinale();
			}

			if (monpals.hlt[monpals.player] <= 0 and (monpals.hlt[0] > 0 or monpals.hlt[1] > 0 or monpals.hlt[2] > 0) and buttonClick != 4)
			{
				buttonClick=4;

				BattleVisuals();

				t = monpals.spc[monpals.player];

				arduboy.setCursor(0, 48);

				Text();

				arduboy.print(F(" was defeated."));
				arduboy.display();
				delay(2000);
			}
			else if (monpals.hlt[0] == 0 and monpals.hlt[1] == 0 and monpals.hlt[2] == 0)
				BattleFinale();
		};
	}

	BattleVisuals();
	BattleMenuVisuals();
}



void MenuVisuals()
{
	arduboy.clear();

	arduboy.setTextColor(WHITE);
	arduboy.setTextBackground(BLACK);

	arduboy.print(gold);
	arduboy.print(F("G"));
	arduboy.setCursor(68, 0);

	arduboy.print(F("Medals:"));
	arduboy.print(medals);
	arduboy.print(F("/4"));

	arduboy.drawBitmap(0, 8, house, 26, 20, WHITE);
	arduboy.drawBitmap(34, 8, shop, 26, 20, WHITE);
	arduboy.drawBitmap(68, 8, dojo, 26, 20, WHITE);
	arduboy.drawBitmap(102, 8, arena, 26, 20, WHITE);

	if (buttonClick == 7)
		i = 8;
	else
		i = 0;

	arduboy.fillRect(0, 48 - i, 128, 16 + i, WHITE);
	arduboy.setTextColor(BLACK);
	arduboy.setTextBackground(WHITE);

	if (buttonClick == 0)
	{
		if (arduboy.everyXFrames(2))
		{
			if (menuCursor == 0)
				arduboy.drawBitmap( 9, 29, characterOne, 8, 8, WHITE);

			if (menuCursor == 1)
				arduboy.drawBitmap( 43, 29, characterOne, 8, 8, WHITE);

			if (menuCursor == 2)
				arduboy.drawBitmap( 77, 29, characterOne, 8, 8, WHITE);

			if (menuCursor == 3)
				arduboy.drawBitmap( 111, 29, characterOne, 8, 8, WHITE);

			delay(100);
		}
		else
		{
			if (menuCursor == 0)
				arduboy.drawBitmap( 9, 29, characterTwo, 8, 8, WHITE);

			if (menuCursor == 1)
				arduboy.drawBitmap( 43, 29, characterTwo, 8, 8, WHITE);

			if (menuCursor == 2)
				arduboy.drawBitmap( 77, 29, characterTwo, 8, 8, WHITE);

			if (menuCursor == 3)
				arduboy.drawBitmap( 111, 29, characterTwo, 8, 8, WHITE);

			delay(100);
		};
	}
	else
	{
		if (buttonClick >= 6)
			arduboy.drawBitmap( 9, 29, characterThree, 8, 8, WHITE);

		if (buttonClick == 4 or buttonClick == 5)
			arduboy.drawBitmap( 43, 29, characterThree, 8, 8, WHITE);

		if (buttonClick == 1 or buttonClick == 2)
			arduboy.drawBitmap( 77, 29, characterThree, 8, 8, WHITE);

		if (buttonClick == 3)
			arduboy.drawBitmap( 111, 29, characterThree, 8, 8, WHITE);
	};
}

void MenuMenuVisuals()
{
	arduboy.setCursor(0, 48);

	if (buttonClick == 0)
	{
		arduboy.print(F("Go where?"));
		arduboy.setCursor(0, 56);

		if (menuCursor == 0)
			arduboy.print(F("<HOME >"));

		if (menuCursor == 1)
			arduboy.print(F("<SHOP >"));

		if (menuCursor == 2)
			arduboy.print(F("<DOJO >"));

		if (menuCursor == 3)
			arduboy.print(F("<ARENA>"));
	};

	if (buttonClick == 1)
	{
		arduboy.print(F("DOJO"));
		arduboy.setCursor(0, 56);

		if (menuCursor == 0)
			arduboy.print(F("<TRAIN>"));

		if (menuCursor == 1)
			arduboy.print(F("<LVLUP>-10G"));
	};

	if (buttonClick == 2 or buttonClick == 7 or buttonClick == 8 or buttonClick == 10 or buttonClick == 11)
	{
		if (buttonClick != 11)
			MonpalSelection();
		else
			MonpalBoxSelection();
	}

	if (buttonClick == 3)
	{
		arduboy.print(F("ARENA"));
		arduboy.setCursor(0, 56);
		arduboy.print(F("(B)CHALLENGE"));
	}

	if (buttonClick == 4)
	{
		arduboy.print(F("SHOP"));
		arduboy.setCursor(0, 56);

		if (menuCursor == 0)
			arduboy.print(F("<BUY ITEMS>"));

		if (menuCursor == 1)
			arduboy.print(F("<BUY MON  >-9G"));
	}

	if (buttonClick == 5)
	{
		arduboy.print(F("Buy what?"));
		arduboy.setCursor(0, 56);

		if (menuCursor == 0)
		{
			arduboy.print(F("<HERB  >x"));
			arduboy.print(herb);
			arduboy.print(F(" -4G"));
		}

		if (menuCursor == 1)
		{
			arduboy.print(F("<COFFEE>x"));
			arduboy.print(coffee);
			arduboy.print(F(" -2G"));
		}

		if (menuCursor == 2)
		{
			arduboy.print(F("<CURE  >x"));
			arduboy.print(cure);
			arduboy.print(F(" -6G"));
		}

		if (menuCursor == 3)
		{
			arduboy.print(F("<REVIVE>x"));
			arduboy.print(revive);
			arduboy.print(F(" -8G"));
		}
	}

	if (buttonClick == 6)
	{
		arduboy.print(F("HOME"));
		arduboy.setCursor(0, 56);

		if (menuCursor == 0)
			arduboy.print(F("<STATS  >"));

		if (menuCursor == 1)
			arduboy.print(F("<MOVE   >"));

		if (menuCursor == 2)
			arduboy.print(F("<RELEASE>"));

		if (menuCursor == 3)
			arduboy.print(F("<SAVE   >"));
	}

	if (buttonClick == 9)
	{
		arduboy.print(F("Which one?"));
		arduboy.setCursor(0, 56);

		if (menuCursor == 0)
			arduboy.print(F("<PARTY>"));

		if (menuCursor == 1)
			arduboy.print(F("<BOX  >"));
	};

	if (buttonClick != 0)
	{
		arduboy.setCursor(84, 56);
		arduboy.print(F("(A)BACK"));
	};
}

void MenuLevelUp()
{
	a = menuCursor;

	MonLvlSpcConstruct();

	MenuVisuals();

	arduboy.setCursor(0, 48);

	if (monpals.mons[a][0] == 0)
		arduboy.print(F("No monpal here."));
	else if (gold < 10)
		arduboy.print(F("Not enough gold."));
	else if (monpals.lvl[a] == 15)
		arduboy.print(F("Level is at max."));
	else if (monpals.lvl[a] < 15)
	{
		monpals.mons[a][0] += 1;
		gold -= 10;
		t = monpals.mons[menuCursor][0];

		BuyMenuVisuals();
		Text();

		arduboy.print(F(" leveled up."));
	};

	arduboy.display();
	delay(2000);
}

void MenuArenaBattle()
{
	MenuVisuals();
	arduboy.setCursor(0, 48);

	if (medals == 4) arduboy.print(F("You have all the medals."));
	else
	{
		GameState = 0;
		buttonClick = 0;
		menuCursor = 0;
		arenaBattle = true;
		arduboy.print(F("You will battle the "));

		if (medals == 0)
			arduboy.print(F("4th nature champion!"));

		if (medals == 1)
			arduboy.print(F("3rd mystic champion!"));

		if (medals == 2)
			arduboy.print(F("2nd synth champion!"));

		if (medals == 3)
			arduboy.print(F("no. 1 champion!"));
	}

	arduboy.display();
	delay(2000);
}

void MenuBuyMon()
{
	BuyMenuVisuals();
	if (gold < 9)
		arduboy.print(F("Not enough gold."));
	else
	{
		NewMon();

		if (b < 3)
		{
			gold -= 9;

			BuyMenuVisuals();

			arduboy.print(F("You got "));

			Text();

			arduboy.print(F("!"));
		}
	}

	arduboy.display();
	delay(2000);
}

void MenuBuyItem()
{
	BuyMenuVisuals();

	if ((gold < 4 and menuCursor == 0) or (gold < 2 and menuCursor == 1) or (gold < 6 and menuCursor == 2) or (gold < 8 and menuCursor == 3))
		arduboy.print(F("Not enough gold."));
	else
	{
		if (menuCursor == 0)
		{
			if (herb == 3)
				arduboy.print(F("Can't carry any more herb."));
			else
			{
				items += 64;
				++herb;
				gold -= 4;
				BuyMenuVisuals();
				arduboy.print(F("You bought a herb."));
			};
		}

		if (menuCursor == 1)
		{
			if (coffee == 3)
				arduboy.print(F("Can't carry any more coffee."));
			else
			{
				items += 16;
				++coffee;
				gold -= 2;
				BuyMenuVisuals();
				arduboy.print(F("You bought a coffee."));
			};
		}

		if (menuCursor == 2)
		{
			if (cure == 3)
				arduboy.print(F("Can't carry any more cure."));
			else
			{
				items += 4;
				++cure;
				gold -= 6;
				BuyMenuVisuals();
				arduboy.print(F("You bought a cure."));
			}
		}
		if (menuCursor == 3)
		{
			if (revive == 3)
				arduboy.print(F("Can't carry any more revive."));
			else
			{
				++items;
				++revive;
				gold -= 8;
				BuyMenuVisuals();
				arduboy.print(F("You bought a revive."));
			}
		}
	}
	arduboy.display();
	delay(2000);
}

void BuyMenuVisuals()
{
	MenuVisuals();
	arduboy.setCursor(0, 48);
}

void Menu()
{
	if(arduboy.justPressed(LEFT_BUTTON) and menuCursor > 0)
	{
		if (buttonClick != 3)
		{
			beep.tone(beep.freq(500), 1);
			--menuCursor;
			/*sound.tone(NOTE_B4, 50);*/
		}
	}

	if(arduboy.justPressed(RIGHT_BUTTON) and ((menuCursor < 3 and buttonClick != 11) or (menuCursor < 14 and buttonClick == 11)))
	{
		if ((buttonClick == 1 or buttonClick == 4 or buttonClick == 9) and menuCursor >= 1)
			menuCursor = 1;
		else if ((buttonClick == 2 or buttonClick == 7 or buttonClick == 8 or buttonClick == 10) and menuCursor >= 2)
			menuCursor = 2;
		else
		{
			if (buttonClick != 3)
			{
				beep.tone(beep.freq(500), 1);
				++menuCursor;
				/*sound.tone(NOTE_B4, 50);*/
			}
		}
	}

	if(arduboy.justPressed(A_BUTTON) and buttonClick != 0)
	{
		beep.tone(beep.freq(500), 1);
		/*sound.tone(NOTE_B4, 50);*/

		if (buttonClick == 1)
		{
			menuCursor = 2;
			buttonClick = 0;
		}
		else if (buttonClick == 2)
		{
			menuCursor = 0;
			buttonClick = 1;
		}
		else if (buttonClick == 3)
		{
			menuCursor = 3;
			buttonClick = 0;
		}
		else if (buttonClick == 4)
		{
			menuCursor = 1;
			buttonClick = 0;
		}
		else if (buttonClick == 5)
		{
			menuCursor = 0;
			buttonClick = 4;
		}
		else if (buttonClick >= 7 and buttonClick <= 9)
		{
			menuCursor = 0;
			buttonClick = 6;
		}
		else if (buttonClick >= 9)
		{
			menuCursor = 0;
			buttonClick = 9;
		}
		else
		{
			buttonClick = 0;
			menuCursor = 0;
		};
	}

	if(arduboy.justPressed(B_BUTTON))
	{
		beep.tone(beep.freq(500));
		delay(67);
		beep.noTone();
		/*sound.tone(NOTE_B4, 50);*/

		if (buttonClick == 10 or buttonClick == 11)
			MonMove();

		if (buttonClick == 9)
		{
			if (menuCursor == 0)
				buttonClick = 10;
			else
				buttonClick = 11;

			menuCursor = 0;
		}

		if (buttonClick == 8)
			MonRelease();

		if (buttonClick == 6)
		{
			if (menuCursor == 0)
				buttonClick = 7;

			if (menuCursor == 1)
				buttonClick = 9;

			if (menuCursor == 2)
				buttonClick = 8;

			if (menuCursor == 3)
				Save();

			if (menuCursor != 3)
				menuCursor = 0;
		}

		if (buttonClick == 5)
			MenuBuyItem();

		if (buttonClick == 4)
		{
			if (menuCursor == 0)
			{
				ItemConstruct();
				buttonClick = 5;
			};

			if (menuCursor == 1)
				MenuBuyMon();
		}

		if (buttonClick == 3)
		{
			MenuArenaBattle();
		}

		if (buttonClick == 2)
		{
			MenuLevelUp();
		}

		if (buttonClick == 1)
		{
			if (menuCursor == 0)
			{
				GameState = 0;
				buttonClick = 0;
			}

			if (menuCursor == 1)
				buttonClick=2;

			menuCursor = 0;
		};

		if (buttonClick == 0 and GameState == 2)
		{
			if (menuCursor == 0)
				buttonClick = 6;

			if (menuCursor == 1)
				buttonClick = 4;

			if (menuCursor == 2)
				buttonClick = 1;

			if (menuCursor == 3)
				buttonClick = 3;

			menuCursor = 0;
		}
	}

	MenuVisuals();
	MenuMenuVisuals();
}

void New()
{
	for (i = 0; i <= 5; i++)
	{
		monpals.mons[i][0] = 0;
		monpals.mons[i][1] = 0;
	}

	for (i = 0; i <= 14; i++)
	{
		boxedMons[i][0] = 0;
		boxedMons[i][1] = 0;
	}

	items = 0;
	gold = 50;
	medals = 0;

	NewMon();
}

void EnemyMonConstruct()
{
	if (arenaBattle == false)
	{
		b = random(3, 6);

		for (i = 3; i <= b; ++i)
		{
			monpals.mons[i][0] = ((random(1, 16) * 16) + (random((medals + 1), ((medals + 1) * 3) + 1)));
			monpals.mons[i][1] = random(0, 256);
		}
	}
	else
	{
		if (medals == 0)
		{
			monpals.mons[3][0] = 49;
			monpals.mons[4][0] = 67;
			monpals.mons[5][0] = 101;
		}

		if (medals == 1)
		{
			monpals.mons[3][0] = 37;
			monpals.mons[4][0] = 231;
			monpals.mons[5][0] = 169;
		}

		if (medals == 2)
		{
		monpals.mons[3][0] = 25;
			monpals.mons[4][0] = 219;
			monpals.mons[5][0] = 125;
		}

		if (medals == 3)
		{
			monpals.mons[3][0] = 95;
			monpals.mons[4][0] = 143;
			monpals.mons[5][0] = 255;
		}

		monpals.mons[3][1] = 255;
		monpals.mons[4][1] = 255;
		monpals.mons[5][1] = 255;
	};
}

void ItemConstruct()
{
	herb = 0;
	coffee = 0;
	cure = 0;
	revive = 0;
	i = items;

	if (i >= 64)
	{
		for (i; i>=64; i-=64)
		{
			++herb;
		}
	}

	if (i >= 16)
	{
		for (i; i>=16; i-=16)
		{
			++coffee;
		}
	}

	if (i >= 4)
	{
		for (i; i>=4; i-=4)
		{
			++cure;
		}
	}

	if (i >= 1)
	{
		for (i; i>=1;--i)
		{
			++revive;
		}
	};
}

void NewMon()
{
	if (monpals.mons[0][0] < 16)
		b = 0;
	else if (monpals.mons[1][0] < 16)
		b = 1;
	else if (monpals.mons[2][0] < 16)
		b = 2;
	else
		b = 3;

	if (b < 3)
	{
		for (i = b; i <= b; ++i)
		{
			monpals.mons[i][0] = 0;
			monpals.mons[i][1] = 0;
			monpals.mons[i][0] = ((random(1, 16) * 16) + 1);
			monpals.mons[i][1] = random(0, 256);
		}

		t = monpals.mons[b][0];
	}
	else
		arduboy.print(F("Party is full."));
}

void Text()
{
	if (t == 0)
		arduboy.print(F("EMPTY"));

	if (t == 1 or (t >=16 and t <= 31))
		arduboy.print(F("AUDIOUSE"));

	if (t == 2 or (t >=32 and t <= 47))
		arduboy.print(F("BEETHRONE"));

	if (t == 3 or (t >=48 and t <= 63))
		arduboy.print(F("BUBBLUE"));

	if (t == 4 or (t >=64 and t <= 79))
		arduboy.print(F("BUNNERINA"));

	if (t == 5 or (t >=80 and t <= 95))
		arduboy.print(F("CHLOROSAUR"));

	if (t == 6 or (t >=96 and t <= 111))
		arduboy.print(F("KRIBBIT"));

	if (t == 7 or (t >=112 and t <= 127))
		arduboy.print(F("MICRUNT"));

	if (t == 8 or (t >=128 and t <= 143))
		arduboy.print(F("OKARD"));

	if (t == 9 or (t >=144 and t <= 159))
		arduboy.print(F("PECAW"));

	if (t == 10 or (t >=160 and t <= 175))
		arduboy.print(F("POLTERGRAB"));

	if (t == 11 or (t >=176 and t <= 191))
		arduboy.print(F("SERPURNT"));

	if (t == 12 or (t >=192 and t <= 207))
		arduboy.print(F("SLUGAMMA"));

	if (t == 13 or (t >=208 and t <= 223))
		arduboy.print(F("SPYMERA"));

	if (t == 14 or (t >=224 and t <= 239))
		arduboy.print(F("SQUEAMASK"));

	if (t == 15 or (t >=240 and t <= 255))
		arduboy.print(F("XENAUCER"));
}

void MonpalSelection ()
{
	arduboy.setCursor(0, 48);

	if (buttonClick == 7)
	{
		MonClearConstruct();

		i = monpals.mons[menuCursor][1];

		MonStatConstruct();

		a = menuCursor;

		MonLvlSpcConstruct();
		MonSpcStatConstruct();

		arduboy.setCursor(0, 40);
		arduboy.print(F("TYPE:"));

		if(monpals.type[menuCursor] == 1)
			arduboy.print(F("NATURE"));
		else if(monpals.type[menuCursor] == 2)
			arduboy.print(F("MYSTIC"));
		else if(monpals.type[menuCursor] == 3)
			arduboy.print(F("SYNTH"));
		else
			arduboy.print(F("NONE"));

		arduboy.setCursor(78, 40);
		arduboy.print(F("L"));
		arduboy.print(monpals.lvl[menuCursor]);
		arduboy.print(F(" H"));
		arduboy.print((((monpals.def[menuCursor] + monpals.maxEng[menuCursor]) / 2) + 1) * monpals.lvl[menuCursor]);
		arduboy.setCursor(48, 48);
		arduboy.print(F(" E"));
		arduboy.print(monpals.maxEng[menuCursor]*2);
		arduboy.print(F(" A"));
		arduboy.print(monpals.atk[menuCursor]);
		arduboy.print(F(" D"));
		arduboy.print(monpals.def[menuCursor]);
		arduboy.print(F(" S"));
		arduboy.print(monpals.spd[menuCursor]);
	}
	else
		arduboy.print(F("Which monpal?"));

	arduboy.setCursor(0, 56);
	t = monpals.mons[menuCursor][0];
	arduboy.print(F("<"));

	Text();

	arduboy.setCursor(66, 56);
	arduboy.print(F(">"));
	arduboy.print(menuCursor + 1);
}

void MonpalBoxSelection ()
{
	arduboy.setCursor(0, 48);
	arduboy.print(F("Which monpal?"));

	arduboy.setCursor(0, 56);
	t = boxedMons[menuCursor][0];
	arduboy.print(F("<"));

	Text();

	arduboy.setCursor(66, 56);
	arduboy.print(F(">"));
	arduboy.print(menuCursor + 1);
}

void MonClearConstruct()
{
	for (i = 0; i <= 5; ++i)
	{
		monpals.type[i] = 0;
		monpals.spc[i] = 0;
		monpals.lvl[i] = 0;
		monpals.maxHlt[i] = 0;
		monpals.hlt[i] = 0;
		monpals.maxEng[i] = 0;
		monpals.eng[i] = 0;
		monpals.atk[i] = 0;
		monpals.def[i] = 0;
		monpals.spd[i] = 0;
		monpals.cdn[i] = 0;
	};
}

void MonSpcStatConstruct()
{
	if (monpals.spc[a] == 1)
	{
		monpals.spd[a] += 3;
		++monpals.def[a];
		++monpals.atk[a];
		monpals.maxEng[a] += 3;
		monpals.type[a] = 3;
	}

	if (monpals.spc[a] == 2)
	{
		monpals.spd[a] += 2;
		monpals.def[a] += 3;
		++monpals.atk[a];
		monpals.maxEng[a] += 2;
		monpals.type[a] = 2;
	}

	if (monpals.spc[a] == 3)
	{
		++monpals.spd[a];
		monpals.def[a] += 3;
		++monpals.atk[a];
		monpals.maxEng[a] += 3;
		monpals.type[a] = 1;
	}

	if (monpals.spc[a] == 4)
	{
		monpals.spd[a] += 3;
		++monpals.def[a];
		monpals.atk[a] += 2;
		monpals.maxEng[a] += 2;
		monpals.type[a] = 1;
	}

	if (monpals.spc[a] == 5)
	{
		monpals.spd[a] += 2;
		monpals.def[a] += 2;
		monpals.atk[a] += 2;
		monpals.maxEng[a] += 2;
		monpals.type[a] = 1;
	}

	if (monpals.spc[a] == 6)
	{
		++monpals.spd[a];
		monpals.def[a] += 3;
		monpals.atk[a] += 3;
		++monpals.maxEng[a];
		monpals.type[a] = 1;
	}

	if (monpals.spc[a] == 7)
	{
		monpals.spd[a] += 2;
		monpals.def[a] += 2;
		++monpals.atk[a];
		monpals.maxEng[a] += 3;
		monpals.type[a] = 3;
	}

	if (monpals.spc[a] == 8)
	{
		++monpals.spd[a];
		++monpals.def[a];
		monpals.atk[a] += 3;
		monpals.maxEng[a] += 3;
		monpals.type[a] = 2;
	}

	if (monpals.spc[a] == 9)
	{
		monpals.spd[a] += 3;
		monpals.def[a] += 2;
		++monpals.atk[a];
		monpals.maxEng[a] += 2;
		monpals.type[a] = 1;
	}

	if (monpals.spc[a] == 10)
	{
		monpals.spd[a] += 2;
		++monpals.def[a];
		monpals.atk[a] += 2;
		monpals.maxEng[a] += 3;
		monpals.type[a] = 2;
	}

	if (monpals.spc[a] == 11)
	{
		monpals.spd[a] += 2;
		++monpals.def[a];
		monpals.atk[a] += 3;
		monpals.maxEng[a] += 2;
		monpals.type[a] = 2;
	}

	if (monpals.spc[a] == 12)
	{
		++monpals.spd[a];
		monpals.def[a] += 3;
		++monpals.atk[a];
		monpals.maxEng[a] += 3;
		monpals.type[a] = 3;
	}

	if (monpals.spc[a] == 13)
	{
		monpals.spd[a] += 3;
		monpals.def[a] += 2;
		++monpals.atk[a];
		monpals.maxEng[a] += 2;
		monpals.type[a] = 3;
	}

	if (monpals.spc[a] == 14)
	{
		monpals.spd[a] += 3;
		monpals.def[a] += 3;
		++monpals.atk[a];
		++monpals.maxEng[a];
		monpals.type[a] = 2;
	}

	if (monpals.spc[a] == 15)
	{
		++monpals.spd[a];
		monpals.def[a] += 2;
		monpals.atk[a] += 2;
		monpals.maxEng[a] += 3;
		monpals.type[a] = 3;
	}
}

void MonLvlSpcConstruct()
{
	for (i = 16; i < 255; i += 16)
	{
		if (monpals.mons[a][0] >= i and monpals.mons[a][0] <= i + 15)
		{
			monpals.spc[a] = i / 16;
			monpals.lvl[a] = monpals.mons[a][0] - i;
		};
	}
}

void MonStatConstruct()
{
	if (i >= 64)
	{
		for (i; i >= 64; i -= 64)
		{
			++monpals.spd[a];
		}
	}

	if (i >= 16)
	{
		for (i; i >= 16; i -= 16)
		{
			++monpals.def[a];
		}
	}

	if (i >= 4)
	{
		for (i; i >= 4; i -= 4)
		{
			++monpals.atk[a];
		}
	}

	if (i >= 1)
	{
		for (i; i >= 1; --i)
		{
			++monpals.maxEng[a];
		}
	}
}

void Save()
{
	c = 459;

	for (i = 0; i <= 2; ++i)
	{
		++c;
		EEPROM.update(c, monpals.mons[i][0]);

		++c;
		EEPROM.update(c, monpals.mons[i][1]);
	}

	for (i = 0; i <= 14; ++i)
	{
		++c;
		EEPROM.update(c, boxedMons[i][0]);

		++c;
		EEPROM.update(c, boxedMons[i][1]);
	}

	EEPROM.update(496, items);
	EEPROM.update(497, gold);
	EEPROM.update(498, medals);

	MenuVisuals();

	arduboy.setCursor(0, 48);
	arduboy.print(F("Game saved!"));
	arduboy.display();
	delay(2000);
}

void Load()
{
	c = 459;

	for (i = 0; i <= 2; i++)
	{
		++c;
		monpals.mons[i][0] = EEPROM.read(c);

		++c;
		monpals.mons[i][1] = EEPROM.read(c);
	}

	for (i=0; i <= 14; i++)
	{
		++c;
		boxedMons[i][0] = EEPROM.read(c);

		++c;
		boxedMons[i][1] = EEPROM.read(c);
	}

	items = EEPROM.read(496);
	gold = EEPROM.read(497);
	medals = EEPROM.read(498);
	GameState = 2;
}

void MonRelease()
{
	MenuVisuals();
	arduboy.setCursor(0, 48);
	if (monpals.mons[menuCursor][0] > 16)
	{
		if (monpals.mons[1][0] == 0 and monpals.mons[2][0] == 0)
			arduboy.print(F("Must have one monpal in party."));
		else
		{
			t = monpals.mons[menuCursor][0];
			monpals.mons[menuCursor][0] = 0;
			monpals.mons[menuCursor][1] = 0;

			//Edit by @Pharap
			if ((monpals.mons[menuCursor][0] == 0) && (monpals.mons[menuCursor + 1][0] > 16) && (menuCursor <= 2))
			{
				// Move the monpals down, one by one
				for (uint8_t i = menuCursor; i < 2; ++i)
				{
					// The next monpal is copied into the current monpal's slot
					monpals.mons[i][0] = monpals.mons[i + 1][0];
					monpals.mons[i][1] = monpals.mons[i + 1][1];
				}

				// Erase the last monpal
				monpals.mons[2][0] = 0;
				monpals.mons[2][1] = 0;
			}

			Text();
			arduboy.print(F(" was released."));
		}
	}
	else
	{
		arduboy.print(F("No monpal here."));
	}

	arduboy.display();
	delay(2000);
}

void MonMove()
{
	MenuVisuals();
	arduboy.setCursor(0, 48);

	if (buttonClick == 11 and boxedMons[menuCursor][0] > 16)
	{
		t = boxedMons[menuCursor][0];

		for (i=0; i <= 2; ++i)
		{
			if (monpals.mons[i][0] < 17)
			{
				monpals.mons[i][0] = boxedMons[menuCursor][0];
				monpals.mons[i][1] = boxedMons[menuCursor][1];
				boxedMons[menuCursor][0] = 0;
				boxedMons[menuCursor][1] = 0;
			}
		}

		if (monpals.mons[2][0] > 16 and boxedMons[menuCursor][0] > 16)
			arduboy.print(F("Party is full."));
		else
		{
			if (boxedMons[menuCursor + 1][0] > 16 and menuCursor != 14)
			{
				for (i = 0; i <= 14; ++i)
				{
					if (boxedMons[i][0] < 17 and i < 14)
					{
						boxedMons[i][0] = boxedMons[i + 1][0];
						boxedMons[i][1] = boxedMons[i + 1][1];
						boxedMons[i + 1][0] = 0;
						boxedMons[i + 1][1] = 0;
					}
				}
			}

			Text();
			arduboy.print(F(" was moved to party."));
		}
	}
	else if (buttonClick == 11 and boxedMons[menuCursor][0] < 17)
		arduboy.print(F("No monpal here."));

	if (buttonClick == 10 and monpals.mons[menuCursor][0] > 16 and monpals.mons[1][0] > 16)
	{
		t = monpals.mons[menuCursor][0];
		for (i = 0; i <= 14; ++i)
		{
			if (boxedMons[i][0] < 17)
			{
				boxedMons[i][0] = monpals.mons[menuCursor][0];
				boxedMons[i][1] = monpals.mons[menuCursor][1];
				monpals.mons[menuCursor][0] = 0;
				monpals.mons[menuCursor][1] = 0;
			}
		}

		if (boxedMons[14][0] > 16 and monpals.mons[menuCursor][0] > 16)
			arduboy.print(F("Box is full."));
		else
		{
			if (monpals.mons[menuCursor+1][0] > 16 and menuCursor != 2)
			{
				for (i=menuCursor; i <= 2; ++i)
				{
					if (monpals.mons[i][0] < 17 and i < 2)
					{
						monpals.mons[i][0] = monpals.mons[i + 1][0];
						monpals.mons[i][1] = monpals.mons[i + 1][1];
						monpals.mons[i + 1][0] = 0;
						monpals.mons[i + 1][1] = 0;
					}
				}
			}

			Text();
			arduboy.print(F(" was moved to box."));
		}
	}
	else if (buttonClick == 10)
	{
		if (monpals.mons[menuCursor][0] < 17)
			arduboy.print(F("No monpal here."));
		else if (monpals.mons[1][0] < 17)
			arduboy.print(F("Must have one monpal in party."));
	}

	arduboy.display();
	delay(2000);
}

void TitleScreen()
{
	monpals.mons[0][0] = EEPROM.read(460);

	arduboy.setTextSize(2);
	arduboy.setCursor(23, 4);
	arduboy.print(F("MONPALS"));
	arduboy.setTextSize(1);
	arduboy.setCursor(36, 56);
	arduboy.print(F("By Revlis"));
	arduboy.setCursor(40, 24);
	arduboy.print(F("(B)NEW"));

	if (monpals.mons[0][0] > 16)
	{
		arduboy.setCursor(40, 34);
		arduboy.print(F("(A)LOAD"));
	}

	if (arduboy.justPressed(B_BUTTON))
	{
		beep.tone(beep.freq(500), 1);
		GameState = 3;
	}

	if (arduboy.justPressed(A_BUTTON) and monpals.mons[0][0] > 16)
	{
		beep.tone(beep.freq(500), 1);
		Load();
	};
}

void Gameloop()
{
	switch (GameState)
	{
		case 0:
			MonConstruct();
			break;
		case 1:
			Battle();
			break;
		case 2:
			Menu();
			break;
		case 3:
			New();
			GameState = 2;
			break;
		case 4:
			TitleScreen();
			break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Game

void setup()
{
	arduboy.boot();
	arduboy.systemButtons();

	arduboy.audio.begin();
	beep.begin();

	arduboy.safeMode();

	arduboy.initRandomSeed();
	arduboy.setTextWrap(true);
	arduboy.setFrameRate(15);

	GameState = 4;
}

void loop()
{
	if (!arduboy.nextFrame())
		return;

	arduboy.pollButtons();

	beep.timer();

	arduboy.clear();

	Gameloop();

	arduboy.display();
}
/////////////////////////////////////////////////////////////////////////////////////////////
