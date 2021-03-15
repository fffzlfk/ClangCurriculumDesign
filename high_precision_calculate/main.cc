#include <iostream>
#include <vector>

// 高精度相加
void add(const std::vector<int> &A, const std::vector<int> &B) {
	const int n = A.size(), m = B.size();
	std::vector<int> C;

	int t = 0;
	for (int i = 0; i < n || i < m; i++) {
		if (i < n) t += A[i];
		if (i < m) t += B[i];
		C.push_back(t % 10);
		t /= 10;
	}
	
	if (t) C.push_back(1); // 高位进位
	
	// 倒序输出
	for (int i = C.size() - 1; ~i; i--)
		printf("%d", C[i]);
	puts("");
}

// 高精度相减
void sub(const std::vector<int> &A, const std::vector<int> &B) {
	const int n = A.size(), m = B.size();
	std::vector<int> C;

	int t = 0; // 向高位的借位
	for (int i = 0; i < n || i < m; i++) {
		if (i < n) t = A[i] - t;
		if (i < m) t -= B[i];
		C.push_back((t + 10) % 10); // t < 0 则向高位借位
		if (t < 0) t = 1;
		else t = 0;
	}

	// 去除前导0
	while (C.size() > 1 && C.back() == 0) C.pop_back();
	
	// 逆序输出
	for (int i = C.size() - 1; ~i; i--)
		printf("%d", C[i]);
	puts("");
}

// 高精度相乘
void mul(std::vector<int> &A, std::vector<int> &B) {
	const int n = A.size(), m = B.size();
	std::vector<int> C(m + n + 1);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			C[i + j] += A[i] * B[j];

	for (int i = 0; i < n + m; i++) {
		C[i + 1] += C[i] / 10;
		C[i] %= 10;
	}

	// 去除前导0
	while (C.size() > 1 && C.back() == 0) C.pop_back();

	// 逆序输出
	for (int i = C.size()-1; ~i; i--)
		printf("%d", C[i]);
	puts("");
}

// 高精度相乘
void div(std::vector<int> &A, int b) {
	std::vector<int> C;
	int r = 0;
	for (int i = 0; i < A.size(); i++) {
		r = r * 10 + A[i];
		C.push_back(r / b);
		r %= b;
	}
	
	// 去除前导0
	while (C.size() > 1 && C.back() == 0) C.pop_back();

	// 逆序输出
	for (int i = C.size()-1; ~i; i--)
		printf("%d", C[i]);
	printf(" reminder = %d\n", r);
}

int main(int argc, char const *argv[]) {
	puts("请输入操作数及运算符");
	char opt;
	std::string a, b;
	std::cin >> a >> opt >> b;
	int d;
	if (opt == '/')
		d = stoi(b);
	const int n = a.length(), m = b.length();
	std::vector<int> A(n), B(m);
	
	// 将数字字符转化为整型
	for (int i = n - 1, j = 0; ~i; i--, j++)
		A[j] = a[i] - '0';
	for (int i = m - 1, j = 0; ~i; i--, j++)
		B[j] = b[i] - '0';
	
	switch (opt) {
		case '+': add(A, B); return 0;
		case '-': sub(A, B); return 0;
		case '*': mul(A, B); return 0;
		case '/': div(A, d); return 0;
	}
	return 0;
}
