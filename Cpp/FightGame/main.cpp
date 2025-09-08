#include <iostream>
#include <locale>
#include <cstdlib>
#include <ctime>

using namespace std;

int getRandomNumber(int start, int end) {
    return rand() % (end - start + 1) + start;
}

void levelUp(int hero[]) {
    hero[2]++; 
    hero[3] += 5; 
    cout << "ÏÎÂÛØÅÍÈÅ ÓÐÎÂÍß! Óðîâåíü: " << hero[2] << ", Ñèëà àòàêè: " << hero[3] << endl;
}

void attack(int hero[], int& monsterHP) {
    int damage = hero[3] + getRandomNumber(-5, 5);
    if (damage < 0) damage = 0;
    
    monsterHP -= damage;
    cout << "Ãåðîé àòàêóåò ìîíñòðà è íàíîñèò " << damage << " óðîíà!" << endl;
    
    if (monsterHP <= 0) {
        monsterHP = 0;
        cout << "Ìîíñòð ïîâåðæåí! Ãåðîé ïîëó÷àåò +20 XP." << endl;
        hero[1] += 20;
        
        if (hero[1] >= 50 * hero[2]) {
            levelUp(hero);
        }
    }
}

void heal(int hero[]) {
    int healing = getRandomNumber(10, 30);
    
    hero[0] += healing;
    if (hero[0] > 100 + (hero[2] - 1) * 20) {
        hero[0] = 100 + (hero[2] - 1) * 20;
    }
    
    cout << "Ãåðîé ëå÷èòñÿ è âîññòàíàâëèâàåò " << healing << " HP." << endl;
}

void monsterAttack(int hero[], int monsterAttack) {
    int damage = monsterAttack + getRandomNumber(-3, 3);
    if (damage < 0) damage = 0;
    
    hero[0] -= damage;
    cout << "Ìîíñòð àòàêóåò è íàíîñèò " << damage << " óðîíà!" << endl;
}

bool tryToRun() {
    return getRandomNumber(0, 1) == 1;
}

int main() {
    
    srand(time(0));
    
    int hero[4] = {100, 0, 1, 20};
    
    cout << "Äîáðî ïîæàëîâàòü â ìèíè-RPG!" << endl;
    cout << "Ãåðîþ ïðåäñòîèò ñðàçèòüñÿ ñ òðåìÿ ìîíñòðàìè!" << endl << endl;
    
    for (int round = 1; round <= 3; round++) {
        int monsterHP = 15 + round * 10;
        int monsterAttackPower = 5 + round * 3;
        
        cout << "Ðàóíä " << round << ": ïîÿâëÿåòñÿ ìîíñòð! HP: " << monsterHP 
             << ", Óðîí: " << monsterAttackPower << endl;
        
        while (hero[0] > 0 && monsterHP > 0) {
            cout << "Ãåðîé: HP=" << hero[0] << ", XP=" << hero[1] << ", LVL=" << hero[2] << endl;
            cout << "Äåéñòâèÿ: 1 - àòàêîâàòü, 2 - ëå÷èòüñÿ, 3 - áåæàòü" << endl;
            cout << "Âûáåðèòå äåéñòâèå: ";
            
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1:
                    attack(hero, monsterHP);
                    break;
                    
                case 2:
                    heal(hero);
                    break;
                    
                case 3:
                    if (tryToRun()) {
                        cout << "Ãåðîé óáåãàåò îò ìîíñòðà!" << endl;
                        monsterHP = 0;
                    } else {
                        cout << "Ïîáåã íå óäàëñÿ! Ìîíñòð áëîêèðóåò ïóòü!" << endl;
                    }
                    break;
                    
                default:
                    cout << "Íåâåðíûé âûáîð! Ãåðîé òåðÿåò õîä." << endl;
                    break;
            }
            
            if (monsterHP > 0 && choice != 3) {
                monsterAttack(hero, monsterAttackPower);
            }
            
            if (hero[0] <= 0) {
                cout << "Ãåðîé ïîãèá! ÈÃÐÀ ÎÊÎÍ×ÅÍÀ." << endl;
                return 0;
            }
            
            cout << endl;
        }
        
        cout << "Ðàóíä " << round << " ïðîéäåí! Ãåðîé ïðîäîëæàåò ïóòü." << endl << endl;
    }

    
    
    cout << "Êîíåö ïðèêëþ÷åíèÿ! Ãåðîé äîñòèã óðîâíÿ " << hero[2] 
         << " ñ " << hero[1] << " XP è " << hero[0] << " HP." << endl;
    
    return 0;
}
