// DynamicArray.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

/*
숙제
    - 정수 데이터를 저장하는 동적 배열 구현하기

    - void Add 함수
        - 맨뒤에 데이터 추가

    - int Size 함수
        - 현재 배열의 크기

    - int Capacity
        - 현재 배열의 용량

    - bool Remove(int value)
        - 특정 값을 찾아서 지우는 함수

    - int Find(int value)
        - 특정 값을 찾는 함수

    - int FindOfIndex(int value)
        - 특정 값의 인덱스를 찾는 함수

    - bool Insert(int value, int findValue)
        - 특정 값을 어떤 값 뒤에 삽입하는 함수 
*/

#include <iostream>

// 동적 배열 정의
class MyArr{
private:
    int size;   // 배열 용량
    int used;   // 현재 배열 크기
    int* arr;   // 동적 배열 포인터  

    void IncreaseCapacity() {
        if (used >= size) {
            std::cout << " (배열 용량 확장)";
            std::cout << " 확장 전 배열의 용량:" << size;
            int newSize = size * 2;
            int* newArr = new int[newSize];

            // 기존 데이터 복사
            for (int i = 0; i < used; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            size = newSize;
            std::cout << " -> 확장 후 배열의 용량:" << size << std::endl;
        }
    }

public:

    // 생성자
    MyArr(int s) {
        size = (s <= 0) ? 1 : s;     // 0 이하의 값이 들어오면 size를 1로 대체 -> if(s<=0) {size = 1}; else{ size = s }; 와 같은 의미
        used = 0;
        arr = new int[size];   // 동적 배열 할당
    }

    // 소멸자
    ~MyArr() {
        delete[] arr;
    }
    
    // 맨뒤에 데이터 추가
    void Add(int value) {
        IncreaseCapacity();        
        arr[used++] = value;    // arr[used]에 value저장 후 used+1
        std::cout << used << "번째 요소에 " << value << " 추가" << std::endl;
    }
        
    // 현재 배열의 크기
    int Size() {
        std::cout << " 현재 배열의 크기:" << used << std::endl;
        return used;
    }
   
    // 현재 배열의 용량
    int Capacity() {
        std::cout << " 현재 배열의 용량:" << size << std::endl;
        return size;
    }
         
    //  특정 값을 찾아서 지우는 함수
    bool Remove(int value) {
        int index = -1;
        for (int i = 0; i < used; i++) {
            if (arr[i] == value) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            std::cout << value << " 을 찾을 수 없음" << std::endl;
            return false;
        }
        for (int j = index; j < used-1; j++) {
            arr[j] = arr[j + 1];    
        }
        used--;
        std::cout << value << " 삭제완료" << std::endl;
        return true;
    }
    
    //  특정 값을 찾는 함수
    bool Find(int value) {
        for (int i = 0; i < used; i++) {
            if (arr[i] == value) {
                std::cout << value << "(" << i << "번 인덱스, " << (i + 1) << "번째 위치)에 존재" << std::endl;
                return true;
            }
        }
        std::cout << value << " 을 찾을 수 없음" << std::endl;        
        return false;
    }
    
    // 특정 값의 인덱스를 찾는 함수
    int FindOfIndex(int value) {
        for (int i = 0; i < used; i++) {
            if (arr[i] == value) {
                std::cout << value << " (" << i << "번 인덱스, " << (i + 1) << "번째 위치)에 존재" << std::endl;
                return i;
            }
        }
        std::cout << value << " 을 찾을 수 없음" << std::endl;
        return -1;
    }

    //  특정 값을 어떤 값 뒤에 삽입하는 함수 : findValue의 인덱스 찾고 그 뒤에 value 추가. 없으면 return false;
    bool Insert(int value, int findValue) {
        int index = -1;        
        for (int i = 0; i < used; i++) {
            if (arr[i] == findValue) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            std::cout << value << "존재하지 않음" << std::endl;
            return false;
        }

        IncreaseCapacity();

        for (int j = used; j > index + 1; j--) {
            arr[j] = arr[j-1];    // 배열 요소값 한칸씩 뒤로 밀기
        }
        arr[index + 1] = value;
        std::cout <<"(삽입): " << value << " " << index + 1 << "번째에 추가" << std::endl;
        used++;
        return true;
    }

    // 배열 값 출력
    void PrintAll() {
        std::cout << "[ ";
        for (int i = 0; i < used; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << "]" << std::endl;
    }
};

int main()
{
    MyArr arr(3);  // 크기 3으로 시작 

    // 값 추가
    arr.Add(10);
    arr.Size();
    arr.Add(20);
    arr.Size();
    arr.Add(30);
    arr.Size();
    arr.Add(40);  // 자동으로 용량 증가
    arr.Size();
    arr.Capacity();

    // 값 찾기
    arr.Find(20);    
    arr.Find(50);    

    // 값 삽입 
    arr.Insert(99, 20);
    arr.Size();
    arr.Capacity();

    // 값 제거
    arr.Remove(30);  // 존재하는 값 제거
    arr.Remove(77);  // 없는 값 제거 시도

    arr.PrintAll();

    arr.Add(77);
    arr.PrintAll();

    arr.Insert(40, 20);
    arr.PrintAll();
    arr.Capacity();
    arr.Size();

    arr.Add(33);
    arr.Capacity();
    arr.Size();

    arr.Remove(40);
    arr.PrintAll();

    MyArr arr_2(10);
    arr_2.Add(1);
    arr_2.Add(2);
    arr_2.Add(3);
    arr_2.Add(4);
    arr_2.Add(5);
    arr_2.Add(6);
    arr_2.Add(7);
    arr_2.Add(8);
    arr_2.Add(9);
    arr_2.Add(10);
    arr_2.PrintAll();


    return 0;
}

