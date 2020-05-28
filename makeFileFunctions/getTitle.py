import sys, requests
from bs4 import BeautifulSoup

PLATFORM = set(['BOJ'])

class MissingTarget(Exception):
    def __init__(self):
        print('ERROR: <문제 플랫폼> <문제 번호> 를 모두 입력해야 합니다.')
        sys.exit()

class WrongType(Exception):
    def __init__(self, expectedType, targetName):
        print('ERROR:', end=' ')
        if targetName is not None:
            print(targetName+'는', end=' ')
        print(expectedType, '형으로 입력해야 합니다.')
        sys.exit()

class WrongPlatform(Exception):
    def __init__(self):
        print('ERROR: <문제 플랫폼>은', PLATFORM, '중 하나여야 합니다.')
        sys.exit()

class FunctionNotExist(Exception):
    def __init__(self, func):
        print('ERROR:', func, '플랫폼의 크롤링 함수가 존재하지 않습니다.')
        sys.exit()

class Crawler:
    def BOJ(self, target_problem):
        req = requests.get('https://www.acmicpc.net/problem/'+str(target_problem))
        html = req.text
        parse = BeautifulSoup(html, 'html.parser')

        problem_title = parse.find("span", {"id": "problem_title"}).text
        return problem_title

def checkTargetPlatform(target_platform):
    try:
        if not target_platform in PLATFORM:
            raise WrongPlatform
    except WrongPlatform:
        pass
        
def getTaget():
    try:
        if (len(sys.argv) < 3):
            raise MissingTarget
        else :
            target_platform = sys.argv[1]
            target_problem = sys.argv[2]
            if not target_platform.isalpha():
                raise WrongType(str, '문제 플랫폼')
            else:
                checkTargetPlatform(target_platform)

            if target_problem.isdigit():
                target_problem = int(target_problem)
            else:
                raise WrongType(int, '문제 번호')
        
        return target_platform, target_problem

    except MissingTarget:
        pass
    except WrongType:
        pass

def getProblemInformation(target_platform, target_problem):
    try:
        crawler = Crawler()
        if (hasattr(crawler, target_platform)):
            func = getattr(crawler, target_platform)
            return func(target_problem)
        else:
            raise FunctionNotExist(target_platform)
    except FunctionNotExist:
        pass
    
def main():
    target_platform, target_problem = getTaget()

    title = getProblemInformation(target_platform, target_problem)
    print(title)
    return title

if __name__ == "__main__":
    main()