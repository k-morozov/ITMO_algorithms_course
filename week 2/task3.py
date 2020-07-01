def main():
    with open('input.txt') as input:
        n = int(input.readline())
        ans = [x for x in range(1, n + 1)]
        for i in range(2, n):
            ans[i], ans[i//2] = ans[i//2], ans[i]

        with open('output.txt', 'w') as output:
            output.write(' '.join(map(str, ans)))


if __name__ == '__main__':
    main()
