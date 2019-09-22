## 팀명 및 팀원
* 팀명 : Hell Maker
* 팀원 : 
*		김도혁  - 주 개발 (타이젠 프로그램)
*		김경남  - 보조 개발 (타이젠 프로그램)
*		이우정  - 기획 
*		유수엽  - 개발 (H/W)
*		김민창  - 디자인 (기구 디자인)

## 프로젝트 제목
* 반려 동물 심폐 소생술 (CPR) 시뮬레이터

## 프로젝트 배경 혹은 목적
* 반려 동물의 죽음으로 인해 생기는 사람들의 슬픔이나 정신적 장애
* 반려동물을 가족으로 생각하는 현상이며, 2020년에는 6조원에 해당하는 큰 시장이고 반려동물을 위한 의료서비스는 지속적으로 발전
* 반려동물의 고령화로 인한 당뇨, 고혈압으로 인해 예방교육이 증가하고 있으며, 이로 인해 CPR ( 심폐소생술) 교육이 필요
* 국내 반려견 CPR 시스템의 부재로 인해 해외에서 수입에 의존하여 사용되는 것을 국내기술로 개발
* 세상에 없는 새로은 제품을 새로운 시장 진출

## 타이젠 오픈소스에 컨트리뷰션한 내역
* 없음


## 파일 리스트

* inc/GPIODigitalIn.h
*	-> GPIO의 인터럽트 및 디지털 입려 처리를 편하게 할수 있는 Class
* inc/GPIODigitalOut.h
*	-> GPIO의 디지털 출력을 편하게 할수 있는 Class
* inc/LiquidCrystal_I2C.h
* src/LiquidCrystal_I2C.cpp
*	-> 아두이노의 I2C LCD라이브러리를 타이젠에 동작하도록 수정
* src/controller.cpp.cpp
*	-> 반력 동물 CPR 시뮬레이터 주처리

## 코드 기여자

* 김도혁
* 	inc/GPIODigitalIn.h			(신규 제작)
* 	inc/GPIODigitalOut.h		(신규 제작)
* 	inc/LiquidCrystal_I2C.h		(아두이노 공개 소수 수정)
* 	src/LiquidCrystal_I2C.cpp 	(아두이노 공개 소스 수정)
*		-> LiquidCrystal_I2C::LiquidCrystal_I2C
*		-> LiquidCrystal_I2C::~LiquidCrystal_I2C()
*		-> LiquidCrystal_I2C::expanderWrite(unsigned char _data)
* 	src/controller.cpp.cpp 	(신규 제작)

## 보드
* RPI3 : GPIO, I2C

## 구현사항
* GPIO / I2C