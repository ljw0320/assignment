#include <iostream>

class Single_List { // 단일 연결리스트
private:
    struct Node{
        std::string Name;   // 노드 이름
        int Value;  // 노드가 갖는 값
        Node* Next; // 다음 노드 포인터

        Node(const std::string& name, int value) {  // 노드 생성자 정의. Node(const std::string& name, int value) : Value(value), Name(name), Next(nullptr){}처럼 간단하게 표현가능
            Value = value;
            Name = name;
            Next = nullptr;
        }   
    };    
    Node* head; // head 선언
    Node* tail; // tail 선언
    Node* target;// 검색으로 발견한 노드 선언

public:    
    Single_List() : head(nullptr), tail(nullptr), target(nullptr){}  // 특수 노드 초기화    

    bool Search(const std::string& TargetName) {  // 노드 검색. 있으면 true , 없으면 false 반환
        Node* NowNode = head;
        while (NowNode != nullptr && NowNode->Name != TargetName){
            NowNode = NowNode->Next;
        }
        if (NowNode == nullptr) {
            std::cout << "삽입 실패: " << TargetName << "찾을 수 없음" << std::endl;
            return false;
        }
        target = NowNode;
        std::cout << target->Name << "확인. 위치:" << target << std::endl;
        return true;       
    }

    void Insert_Head(const std::string& NewName, int Value) // Head에 값 삽입               
    {  
        Node* newNode = new Node(NewName, Value);   
        newNode->Next = head;   // 기존 head의 포인터를 삽입한 노드의 다음 노드 포인터로 정의 ex) 삽입 전:head -> next , 삽입 후:newnode->head
        head = newNode; 
        if (tail == nullptr) tail = newNode;  // #리스트가 처음 비어 있었던 경우        
        std::cout << head->Name << "삽입(head)." << std::endl;
        return;
    }

    void Insert_Tail(const std::string& NewName, int Value) // Tail에 삽입                
    {  
        Node* newNode = new Node(NewName, Value);   // 노드 생성
        if (tail == nullptr) {
            head = tail = newNode;
        }else {
            tail->Next = newNode;   // 기존 tail의 다음 노드 포인터를 삽입한 노드의 포인터로 정의 ex) 삽입 전:node -> tail , 삽입 후:tail->newnode
            tail = newNode; // head 초기화
        }
        std::cout << tail->Name << "삽입(tail)." << std::endl;
        return;
    }
    
    void Insert(const std::string& TargetName, const std::string& NewName, int Value) // 특정 노드 뒤에 어떤 값을 삽입(nownode->next => nownode->newnode->next)
    {  
        if (!Search(TargetName)) {
            std::cout << "삽입 실패: " << TargetName << "찾을 수 없음" << std::endl;
            return;
        }else {
            Node* newNode = new Node(NewName, Value);   // 노드 생성                
            newNode->Next = target->Next;
            target->Next = newNode;
            if (target == tail) tail = newNode;  // 마지막 노드 뒤에 삽입한 경우 tail 갱신            
            std::cout << newNode->Name << "삽입. 위치: "<< newNode << std::endl;
            return;
        }               
    }

    void Delete(const std::string& TargetName) // 노드 삭제(previous->nownode->next => previous->next) 
    {   
        if (!Search(TargetName)) {
            std::cout << "삭제 실패: " << TargetName << "찾을 수 없음" << std::endl;
            return;
        }
        // 삭제 대상이 head일 경우
        if (target == head) {
            head = head->Next;
            if (target == tail) tail = nullptr;  // 노드가 하나뿐이었다면 tail도 nullptr            
            std::cout << target->Name << "(head) 삭제" << std::endl;
            delete target;            
            return;
        }
        // 중간 또는 마지막 노드 삭제        
        Node* prev = head;
        while (prev->Next != target) {   // 다음 노드 포인터가 target이 나올 때까지 반복
            prev = prev->Next;
        }
        prev->Next = target->Next;  // 타겟 노드의 다음 노드 포인터를 타겟 이전 노드의 다음 포인터로 초기화
        if (target == tail) tail = prev;  // 삭제 대상이 tail이면 tail 갱신        
        std::cout << target->Name << "삭제" << std::endl;
        delete target;
        return;                
    }
    void Print() {  // 연결 리스트 출력
    /*if (head = nullptr) {
            std::cout << "리스트 비어있음" << std::endl;
            return;
        }
        Node* NowNode = head;
        while (NowNode->Next != nullptr) {
            std::cout << NowNode->Name << "(값:" << NowNode->Value << ")->";
            NowNode = NowNode->Next;
        }
        std::cout << NowNode->Name << "(값:" << NowNode->Value << ")" << std::endl;
        return;*/
        if (head == nullptr) {
            std::cout << "리스트 비어 있음" << std::endl;
            return;
        }
        Node* NowNode = head;
        while (NowNode != nullptr) {
            std::cout << NowNode->Name << "(값:" << NowNode->Value << ")";
            if (NowNode->Next != nullptr) std::cout << "->";
            NowNode = NowNode->Next;
        }
        std::cout << std::endl;
        return;
    }
};

class Double_List { // 이중 연결리스트
private:
    struct Node {
        std::string name;
        int Value;
        Node* Prev;        
        Node* Next;
        Node(const std::string& Name, int value) : name(Name), Value(value), Prev(nullptr), Next(nullptr) {}
    };
    Node* head;   // 첫 번째 노드
    Node* tail;   // 마지막 노드
    Node* target;

public:
    Double_List() : head(nullptr), tail(nullptr), target(nullptr){}

    bool Search(const std::string& TargetName) {    // 노드 검색
        Node* nowNode = head;
        std::cout << TargetName << " 검색 시작" << std::endl;
        while (nowNode != nullptr && nowNode->name != TargetName) {
            nowNode = nowNode->Next;
        }
        std::cout << TargetName << " 검색 종료" << std::endl;
        if (nowNode == nullptr) {
            std::cout << TargetName << " 찾을 수 없음" << std::endl;
            return false;
        }else {
            target = nowNode;
            std::cout << nowNode->name << " 발견" << std::endl;
            return true;
        }
    }

    void Insert_Head(const std::string& Name, int Value) {  // head에 노드 삽입                
        Node* newNode = new Node(Name, Value);

        if (head == nullptr) head = tail = newNode;  // 처음 노드
        else
        {
            head->Prev = newNode; 
            newNode->Next = head; 
            head = newNode; 
        }        
        std::cout << "head에 " << Name <<"삽입"<< std::endl;
        return;
    }

    void Insert_Tail(const std::string& Name, int Value) { // tail에 노드 삽입
        Node* newNode = new Node(Name, Value);

        if (tail = nullptr) head = tail = newNode;
        else
        {
            tail->Next = newNode;   
            newNode->Prev = tail;   
            tail = newNode;
        }        
        std::cout << "tail에 " << Name << "삽입" << std::endl;
        return;
    }

    void Insert(const std::string& TagrgetName, const std::string& newName, int Value) {    // 중간에 노드 삽입        
        if (!Search(TagrgetName)) return;
        else {
            Node* newNode = new Node(newName, Value);
            newNode->Next = target->Next;   // target->next => target->newnode->next
            newNode->Prev = target;
            target->Next = newNode;
            std::cout << newName << TagrgetName << "뒤에 생성" << std::endl;
            return;
        }
    }
    void Delete(const std::string& TargetName) {  // 대상 노드 삭제
        if (!Search(TargetName)) return;
        else {            
            if (target == head && target == tail) {  // 노드 1개
                head = tail = nullptr;
            }
            else if (target == head) {
                head = head->Next;
                head->Prev = nullptr;
            }
            else if (target == tail) {
                tail = tail->Prev;
                tail->Next = nullptr;
            }
            else {
                target->Prev->Next = target->Next;
                target->Next->Prev = target->Prev;
            }            
            delete target;  // prev->target->next
            std::cout << TargetName << " 삭제" << std::endl;
            return;
        }
    }
    void Print() {  // List 상태 확인        
        if (head == nullptr) {
            std::cout << "리스트 비어 있음" << std::endl;
            return;
        }
        Node* current = head;
        while (current!= nullptr) {
            std::cout << current->name << "->";
            current = current->Next;            
        }        
        std::cout << std::endl;
        return;       
    }
};

int main()
{
    Single_List List1;    
    List1.Insert_Head("노드1", 1);
    List1.Insert("노드1", "노드3", 3);
    List1.Insert("노드1", "노드2", 2);
    List1.Print();
    List1.Delete("노드3");
    List1.Print();
    List1.Insert("노드2", "노드3", 3);
    List1.Insert("노드3", "노드4", 4);
    List1.Print();

    Double_List dList1;
    dList1.Insert_Head("노드1", 10);
    dList1.Print();
    dList1.Insert_Head("노드2", 20);    
    dList1.Print();
    dList1.Insert_Head("노드3", 30);
    dList1.Print();
    dList1.Insert("노드2", "노드2-1", 21);
    dList1.Print();
    dList1.Delete("노드2-1");
    dList1.Print();
    dList1.Delete("노드1");
    dList1.Print();
}


/*

주요 연산
    - 삽입(Insert)
        - 처음, 중간, 끝에 삽입
        - 시간복잡도
            - O(1) 처음
            - O(n) 중간
            - 끝(구현에 따라 다름 O(1), O(n))
    - 삭제(Delete)
        - 특정 노드 삭제
        - 시간복잡도
            - O(1) 처음, 끝 (Tail 정보가 있으면)
            - O(n) 중간
    - 탐색(Find or Search)
        - 값 또는 위치로 찾기
        - 시간 복잡도
            - O(n)
    - 순회
        - 시간복잡도
            - O(n)
    - 배열과 달리 인덱스로 접근이 불가능하며, 순차 탐색이 필요함

링크드 리스트의 장단점
    - 장점
        - 동적 메모리 할당 가능(크기 고정이 아님)
        - 삽입/삭제가 빠름(배열처럼 이동 필요 없음)
    - 단점
        - 임의 접근 불가(랜덤 접근 불가능)
        - 캐시 효율성이 낮음(배열대비)

배열 vs 리스트
    - 배열과 리스트를 순회하면 뭐가 더 빠른가?
        - 배열은 연속적인 메모리이고, 리스트는 비연속적인 메모리 이기 때문에 배열이 더 빨리 순회를 할 수 있습니다.
    - 뭔가 데이터를 찾는다면 뭐가 더 빠른가?
        - 배열이 빠름
    - 뭔가 데이터를 삭제하는 것은 뭐가 더 빠른가?
        - 뭔가 데이터를 찾고 삭제를 한다
            - 
    - 데이터 삽입
        - 리스트의 삭제 시간복잡도는 O(1)
        - 배열의 삭제 시간복잡도는 O(N)

배열 vs 리스트 기본 개념 비교
    - 메모리 저장 방식
        - 동적 배열
            - 연속된 메모리 공간에 저장
        - 링크드 리스트
            - 불연속적인 메모리 공간에 저장
    - 요소 접근 방식
        - 동적 배열
            - 인덱스를 통한 임의 접근이 가능
        - 링크드 리스트
            - 순차 접근 필요
    - 삽입/삭제 성능
        - 동적 배열
            - 중간 삽입/삭제 시 비효율적
        - 링크드 리스트
            - 중간 삽입/삭제가 효율적
    - 메모리 사용
        - 동적 배열
            - 연속된 메모리
            - 데이터만 저장
        - 링크드 리스트
            - 불연속 메모리
            - 데이터 + 포인터 저장 메모리 오버헤드가 있음
    
연산 성능 비교
    - 접근
        - 동적 배열
            - O(1)
        - 링크드 리스트
            - O(n)
    - 끝에 삽입
            - 동적 배열
                - O(1)
            - 링크드 리스트
                - Tail 유무에 따라 O(n), O(1)
    - 중간 삽입
            - 동적 배열
                - O(n), 데이터 이동 필요
            - 링크드 리스트
                - O(1), 노드 생성 및 포인터 조정
    - 삭제
            - 동적 배열
                - O(n), 데이터 이동 필요
            - 링크드 리스트
                - O(1), 노드 생성 및 포인터 조정
    - 메모리 재할당
        - 동적 배열
            - 용량 초과시 필요
        - 링크드 리스트
            - 필요 없음
    - 캐시 성능
        - 동적 배열
            - 연속 메모리이기 때문에 좋음
        - 링크드리스트
            - 불연속 메모리이기 때문에 나쁨

*/

