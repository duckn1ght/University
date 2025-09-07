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
    cout << "��������� ������! �������: " << hero[2] << ", ���� �����: " << hero[3] << endl;
}

void attack(int hero[], int& monsterHP) {
    int damage = hero[3] + getRandomNumber(-5, 5);
    if (damage < 0) damage = 0;
    
    monsterHP -= damage;
    cout << "����� ������� ������� � ������� " << damage << " �����!" << endl;
    
    if (monsterHP <= 0) {
        monsterHP = 0;
        cout << "������ ��������! ����� �������� +20 XP." << endl;
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
    
    cout << "����� ������� � ��������������� " << healing << " HP." << endl;
}

void monsterAttack(int hero[], int monsterAttack) {
    int damage = monsterAttack + getRandomNumber(-3, 3);
    if (damage < 0) damage = 0;
    
    hero[0] -= damage;
    cout << "������ ������� � ������� " << damage << " �����!" << endl;
}

bool tryToRun() {
    return getRandomNumber(0, 1) == 1;
}

int main() {
    
    srand(time(0));
    
    int hero[4] = {100, 0, 1, 20};
    
    cout << "����� ���������� � ����-RPG!" << endl;
    cout << "����� ��������� ��������� � ����� ���������!" << endl << endl;
    
    for (int round = 1; round <= 3; round++) {
        int monsterHP = 15 + round * 10;
        int monsterAttackPower = 5 + round * 3;
        
        cout << "����� " << round << ": ���������� ������! HP: " << monsterHP 
             << ", ����: " << monsterAttackPower << endl;
        
        while (hero[0] > 0 && monsterHP > 0) {
            cout << "�����: HP=" << hero[0] << ", XP=" << hero[1] << ", LVL=" << hero[2] << endl;
            cout << "��������: 1 - ���������, 2 - ��������, 3 - ������" << endl;
            cout << "�������� ��������: ";
            
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
                        cout << "����� ������� �� �������!" << endl;
                        monsterHP = 0;
                    } else {
                        cout << "����� �� ������! ������ ��������� ����!" << endl;
                    }
                    break;
                    
                default:
                    cout << "�������� �����! ����� ������ ���." << endl;
                    break;
            }
            
            if (monsterHP > 0 && choice != 3) {
                monsterAttack(hero, monsterAttackPower);
            }
            
            if (hero[0] <= 0) {
                cout << "����� �����! ���� ��������." << endl;
                return 0;
            }
            
            cout << endl;
        }
        
        cout << "����� " << round << " �������! ����� ���������� ����." << endl << endl;
    }
    
    cout << "����� �����������! ����� ������ ������ " << hero[2] 
         << " � " << hero[1] << " XP � " << hero[0] << " HP." << endl;
    
    return 0;
}