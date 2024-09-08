# Vehicle_SENSOR_Project
차량 사고 방지 프로젝트입니다.

## 개요
![image](https://github.com/user-attachments/assets/bbd78ac0-c227-40ee-80a7-2e6805156c14)

- 위 통계 그래프를 보면, 최근 10년간 매년 교통사고 수가 높은 수치를 보인다.운전 시 언제 어떤일이 발생할지 모른다는 사실을 알기 때문에 주의를 기울일 필요가 있다고 생각하여 이를 보조해주기 위한 시스템을 목표로 설정하였습다.

## 구성도
![image](https://github.com/user-attachments/assets/b893f8c5-b50b-457a-b7cc-32d206752f1f)

- PC에서 코드를 구현하여 WiringPi를 통해 Raspberry pi로 전송하고 각 센서들을 구동하도록 설계하였습니다.

## 회로 구성
![image](https://github.com/user-attachments/assets/e33361aa-37f7-4ac1-8a34-90694894a1f3)

## 플로우 차트
![image](https://github.com/user-attachments/assets/c23117af-bdf3-4c37-9ade-0c1c6e4248d5)

- 초음파 센서로 거리를 측정하고 거리 별로 임계값을 설정해 LCD에 문구를 출력하고, 부저를 통해 사용자에게 알려주는 알고리즘입니다.

## 구현 결과
![image](https://github.com/user-attachments/assets/9b6a3e7d-cd4e-4859-bd2f-46947b20d70a)

- 거리가 20cm, 10cm 이내에 들어왔을 때의 시연 모습

## 시연 영상
* test.mp4
