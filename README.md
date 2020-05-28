# AlgorithmProblemFormatter (aka. 알잘딱깔센 포멧터)
알고리즘 repo의 README를 정리해 보겠다며 허구한 날 문제 제목 복붙하던 사람의 귀찮은 작업을 컴퓨터에게 떠넘기려는 계략

---

## 프로젝트 시작 배경

알고리즘 문제를 풀고 [깃허브 repo](https://github.com/kjh107704/Algorithm)의 `README.md`에 풀었던 문제들을 기록하려는 습관을 기르고 있다.

여기서 발생한 문제. 문제 제목 복붙이 너무 귀찮다.

귀찮은 반복 작업이니 컴퓨터한테 시켜야지. 이왕이면 이런 저런 기능 붙여서!

---

## 프로젝트 진행 상황

- [x] 제목 가져오는 크롤러 만들기 - [#1](https://github.com/kjh107704/AlgorithmProblemFormatter/issues/1)
- [ ] `MAKE` 명령어를 이용하여 `target_plateform`별로 정해진 형식으로 파일 만들기
- [ ] `git push` 명령어 실행 시, 자동으로 `README.md` 업데이트하기


---

## 프로그램 환경

### main.cpp

- **C++17 이상 필요** 
  - `experimental/filesystem` 라이브러리 사용
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp) 사용 
  - `/makeFileFUnctions/dist/`에 실행시 필요한 헤더들 포함되어 있음