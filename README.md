> 깃허브의 Repo가 복수개인 경우, Repo마다 README.md를 만들어주세요.

## 팀명 및 팀원
* 간단히 적어주세요.
* 팀원이 맡은 역할을 자유롭게 적어주세요(기획/디자인/설계/개발/디버깅/기술조언/환경설정/발표 등)

## 프로젝트 제목
* 간단히 적어주세요.

## 프로젝트 배경 혹은 목적
* 간단히 적어주세요.

## 타이젠 오픈소스에 컨트리뷰션한 내역
* 팀원이 소스를 타이젠 오픈소스에 컨트리뷰션한 경우에만 적어주세요.
* 커밋을 타이젠 측에서 리뷰하고 있다면, '리뷰 중'이라고 적어주세요.
* 커밋이 최종적으로 반영되었다면, '반영 완료'라고 적어주세요.
* 커밋이 최종적으로 거절당했다면, '반영 실패'라고 적어주세요.
* 커밋한 내용을 확인할 수 있는 주소를 적어주세요.
* 예시
  * 리뷰 중, https://review.tizen.org/gerrit/#/c/profile/iot/apps/native/homescreen-efl/+/213918/
  * 반영 완료, https://review.tizen.org/gerrit/#/c/apps/native/smartthings-thing-service/+/213867/

## 파일 리스트
* 팀원이 소스 파일을 직접 만든 경우, 해당 파일을 적어주세요.
* 오픈소스(타이젠 등)로부터 가져왔지만, 팀원이 내용을 수정하거나 덧붙인 경우, 해당 파일을 적어주세요.
* 오픈소스(타이젠 등)를 그대로 가져다가 사용한 파일은 적지 말아주세요.
* 헤더와 소스만 적어주세요.
* 디자인 등의 리소스는 적지 말아주세요.
* 예시
  * inc/resource_1.h
  * inc/resource_2.h
  * src/resource_1.c
  * src/resource_2.c

## 코드 기여자
* 각자 개발한 코드를 빠짐없이 기입해주세요.
* 파일 단위 혹은 함수 단위로 적어주세요.
* 라인 단위로는 적지 말아주세요.
* 팀원의 이름을 반드시 명시해주세요.
* 예시
  * 철수가 파일 전체를 개발한 경우
    * inc/resource_1.h 철수
    * src/resource_1.c 철수
  * 철수와 영희가 각각 특정 파일의 함수를 개발한 경우
    * src/resource_2.c function_1 영희
    * src/resource_2.c function_2 철수
  * 영희가 오픈소스에 특정 함수를 개발한 경우
    * src/tizen.c function_3 영희

## 보드
* 프로젝트에서 사용하는 보드(RPI3 or SDTA7D)를 적어주세요.
* 사용하는 보드마다 각각의 목적을 적어주세요.
* 사용하는 보드마다 설치되는 깃허브의 Repo를 적어주세요.
* 예시 : 한 대만 사용한 경우
  * RPI3 : 이미지 분석 및 센서 연동, github.com/theojin/hackathon-example
* 예시 : 서로 다른 모델의 보드를 두 대 이상 사용한 경우
  * RPI3 : 이미지 분석, github.com/theojin/hackathon-example-1
  * SDTA7D : 센서 연동, github.com/theojin/hackathon-example-2
* 예시 : 동일 모델을 두 대 이상 사용한 경우
  * RPI3 1 : 이미지 분석, github.com/theojin/hackathon-example-1
  * RPI3 2 : 센서 연동, github.com/theojin/hackathon-example-2

## 구현사항
* GPIO / I2C / PWM / UART / SPI 중 사용한 프로토콜 명시
* 누비슨 클라우드 / 싱스파크 클라우드 / 기타 중 사용한 클라우드 명시
* 카메라 기능 사용 여부
* 이미지 분석 기능 사용 여부
* 예시
  * GPIO 사용
  * 싱스파크 클라우드 사용
  * 카메라 사용하지 않음
  * 이미지 분석 사용하지 않음
