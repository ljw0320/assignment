// HW#1_250509.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>

enum ElementType {FIRE, WATER, EARTH, WIND};  // 0: 불, 1: 물, 2: 땅, 3: 바람

class Monster {
private:
    std::string strName;
    int iHp;
    int iAtk;
    int iDef;    
    //int iElement;   // 0: 불,  1:물,  2:땅, 3:바람
    ElementType iElement;

public:
    Monster(std::string name, int hp, int atk, int def, ElementType element)
        : strName(name), iHp(hp), iAtk(atk), iDef(def), iElement(element) {}

  void ShowData() {    // 대상 정보 표시    
      std::string Element;
      switch (iElement)
      {
        case 0: Element = "불"; break;
        case 1: Element = "물"; break;
        case 2: Element = "땅"; break;
        case 3: Element = "바람"; break;
      }
        std::cout << "이름: " << strName;
        std::cout << ", HP: " << iHp;
        std::cout << ", 공격력: " << iAtk;
        std::cout << ", 방어력: " << iDef;         
        std::cout << ", 속성: " << Element << std::endl;
   }

    int SelfHarm(int damage) {
        iHp = iHp - damage;
        if (iHp < 0) iHp = 0;
        return iHp;
    }   

    // 속성 (불, 물, 땅, 바람)	= (0, 1, 2, 3)    
       
    float compatibility(Monster& target) const { // 상성 계산 함수(데미지에 곱해짐)
        if (target.iElement == iElement) return 1.0;        
        else if (target.iElement == FIRE) // 상대 속성(불은 바람에 강하나 물과 땅에는 약함)
        {   
            switch (iElement) { // 내 속성             
                case WATER: return 1.5f; break;
                case EARTH: return 1.5f; break;
                case WIND: return 0.5f; break;
            }
        }
        else if (target.iElement == WATER) // 상대 속성(물은 불에 강하나 바람에게는 약함)
        {   
            switch (iElement) { // 내 속성           
                case FIRE: return 0.5f; break;
                case EARTH: return 1.0f; break;
                case WIND: return 1.5f; break;
            }
        }
        else if (target.iElement == EARTH) // 상대 속성(땅은 불에게 강하나 바람에 약함)
        {   
            switch (iElement) { // 내 속성              
                case FIRE: return 0.5f; break;
                case WATER: return 1.0f; break;
                case WIND: return 1.5f; break;
            }
        }
        else if (target.iElement == WIND) // 상대 속성(바람은 땅과 물에 강하나 불에는 약함)
        {   
            switch (iElement) { // 내 속성
                case FIRE: return 1.5f; break;
                case WATER: return 0.5f; break;
                case EARTH: return 0.5f; break;
            }
        }
        return 1.0f;
    }
    
    int Attack(Monster& target) {   // target : 공격 대상       
        int iDeal = iAtk - target.iDef;
        iDeal = iDeal * compatibility(target);                
        if (iDeal < 1)  iDeal = 1;        
        target.iHp = target.iHp - iDeal;
        std::cout << strName << " 이/가 " << target.strName << "에게 " << iDeal << " 데미지! " << target.strName <<"의 남은 체력 : " << target.iHp << std::endl;
        return iDeal;                
    }
   
};
int main()
{
    Monster Player("이정욱", 100, 20, 5, FIRE);   // hp = 100, 공격력 20, 방어력 5, 불속성 
    Player.ShowData();
    Monster Bear("Kuma", 150, 50, 10, EARTH);   // hp = 150, 공격력 50, 방어력 10, 땅속성
    Bear.ShowData();

    Player.Attack(Bear);  

    Bear.Attack(Player);    

    return 0;


}

