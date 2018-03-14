#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<unordered_map>
using namespace std;
class quick {
public:
	int partition(vector<int>& num, int left, int right) {
		int pivot = num[left];
		int l = left + 1, r = right;
		while (l <= r) {
			if (num[l] > pivot&&num[r] < pivot) {
				swap(num[l++], num[r--]);
			}
			if (num[l] <= pivot) {
				l++;
			}
			if (num[r] >= pivot) {
				r--;
			}
		}
		swap(num[left], num[r]);
		return r;
	}
	void helper(vector<int>& num, int left, int right) {
		if (left >= right) {
			return;
		}
		int pos = partition(num, left, right);
		helper(num, 0, pos - 1);
		helper(num, pos + 1, right);
	}
};
class heap {
public:
	void adjustHeap(vector<int>& num, int idx, int end) {
		int flag = idx;
		int left = 2 * idx + 1;
		int right = 2 * idx + 2;
		if (left < end&&num[left] > num[flag]) {
			flag = left;
		}
		if (right < end&&num[right] > num[flag]) {
			flag = right;
		}
		if (flag != idx) {
			swap(num[flag], num[idx]);
			adjustHeap(num, flag, end);
		}
	}
	void build_min_heap(vector<int>& num) {
		int heap_size = num.size();
		for (int i = heap_size / 2 - 1; i >= 0; i--) {
			adjustHeap(num, i, heap_size);
		}
	}
};
class shell {
public:
	void shellInsert(vector<int>& num, int d) {
		for (int i = 0; i < d; i++) {
			for (int j = i + d; j < num.size(); j += d) {
				int tmp = num[j];
				int k = j - d;
				while (k >= 0 && num[k] > num[j]) {
					num[k + d] = num[k];
					k -= d;
				}
				num[k + d] = tmp;
			}
		}
	}
};
class mergeN {
public:
	void merge(vector<int>& num, int left, int mid, int right) {
		vector<int> tmp;
		int i = left, j = mid + 1;
		while (i <= mid && j <= right) {
			if (num[i] <= num[j]) {
				tmp.push_back(num[i++]);
			}
			else {
				tmp.push_back(num[j++]);
			}
		}
		while (i <= mid) {
			tmp.push_back(num[i++]);
		}
		while (j <= right) {
			tmp.push_back(num[j++]);
		}
		for (int i = 0; i < tmp.size(); i++) {
			num[left + i] = tmp[i];
		}
	}
	void msort(vector<int>& num, int left, int right) {
		if (left < right) {
			int mid = (left + right) / 2;
			msort(num, left, mid);
			msort(num, mid + 1, right);
			merge(num, left, mid, right);
		}
	}
};
class radix {
public:
	void radixHelp(vector<int>& num, int exp) {
		vector<int> range(10, 0);
		//��push_back��Щ��vector���в�����ʱ����Բ���ʼ����С�����������鷽ʽ���±���룩���и�ֵ��Ҫ���г�ʼ��
		vector<int> tmp(num.size(), 0);
		for (int i = 0; i < num.size(); i++) {
			range[(num[i] / exp) % 10]++;
		}
		for (int i = 1; i < range.size(); i++) {
			range[i] += range[i - 1];
		}
		for (int i = num.size() - 1; i >= 0; i--) {
			tmp[range[(num[i] / exp) % 10] - 1] = num[i];
			range[(num[i] / exp) % 10]--;
		}
		num = tmp;
	}
};
class solution {
public:
	void printOut(const vector<int>& num) {
		for (int i = 0; i < num.size(); i++) {
			cout << num[i] << " ";
		}
		cout << endl;
	}
	void bubbleSort(vector<int>& num) {
		cout << "ð������ʱ�临�Ӷ�O(N2)���ռ临�Ӷ�O(1)" << endl;
		int len = num.size();
		if (len == 0) {
			return;
		}
		for (int i = 0; i < len - 1; i++) {
			for (int j = len - 1; j > i; j--) {
				if (num[j] < num[j - 1]) {
					swap(num[j], num[j - 1]);
				}
			}
		}
	}
	void selectSort(vector<int>& num) {
		cout << "ѡ������ʱ�临�Ӷ�O(N2)���ռ��զ��O(1)" << endl;
		int len = num.size();
		if (len == 0) {
			return;
		}
		for (int i = 0; i < len-1; i++) {
			int flag = i;
			for (int j = i + 1; j < len; j++) {
				if (num[flag] > num[j]) {
					flag = j;
				}
			}
			if (flag != i)
				swap(num[i], num[flag]);
		}
	}
	void insertSort(vector<int>& num) {
		cout << "��������ʱ�临�Ӷ�O(N2)���ռ临�Ӷ�O(1)" << endl;
		int len = num.size();
		if (len == 0) {
			return;
		}
		for (int i = 1; i < len; i++) {
			int j = i;
			int target = num[i];
			while (j > 0 && target < num[j - 1]) {
				num[j] = num[j - 1];
				j--;
			}
			num[j] = target;
		}
	}
	void quickSort(vector<int>& num) {
		quick q;
		cout << "����ʱ�临�Ӷ�O(NlogN)���ҪO(N2)���ռ临�Ӷ�O(logN)-O(N)" << endl;
		int len = num.size();
		if (len == 0) {
			return;
		}		
		q.helper(num, 0, num.size()-1);
	}
	void heapSort(vector<int>& num) {
		heap h;
		cout << "������ʱ�临�Ӷ�O(NlogN)���ռ临�Ӷ�O(1)" << endl;
		int len = num.size();
		if (len == 0) {
			return;
		}
		int heap_size = num.size();
		h.build_min_heap(num);
		for (int i = heap_size - 1; i >= 0; i--) {
			swap(num[0], num[i]);
			h.adjustHeap(num, 0, i);
		}
	}
	void shellSort(vector<int>& num) {
		shell sh;
		cout << "ϣ������ʱ�临�Ӷ�O(1.3N)���ռ临�Ӷ�O(1)" << endl;
		int len = num.size();
		if (len == 0) {
			return;
		}
		int d = num.size() / 2;
		while (d >= 1) {
			sh.shellInsert(num, d);
			d /= 2;
		}
	}	
	void mergeSort(vector<int>& num) {
		mergeN mg;
		cout << "�鲢����ʱ�临�Ӷ�O(NlogN),�ռ临�Ӷ�O(N)" << endl;
		int len = num.size();
		if (len == 0) {
			return;
		}
		mg.msort(num, 0, num.size() - 1);
	}
	void countSort(vector<int>& num) {
		cout << "��������ʱ�临�Ӷ�O(N)���ռ临�Ӷȿ����" << endl;
		//���������������Ͱ���򣬰Ѽ�ֵ����Ͱ���±�
		int len = num.size();
		if (len == 0) {
			return;
		}
		unordered_map<int, int> count;
		for (auto n : num) {
			count[n]++;
		}
		int pos = 0;
		int max = *max_element(num.begin(), num.end());
		for (int i = 0; i <= max; i++) {
			for (int j = 0; j < count[i]; j++) {
				num[pos++] = i;
			}
		}
	}
	void radixSort(vector<int>& num) {
		radix r;
		cout << "��������ʱ�临�Ӷ�O(d(N+rd)),�ռ临�Ӷ�O(rd),����rΪ��������radix��ȡֵ��Χ��ʮ���ƾ���10��dΪλ��." << endl;
		int len = num.size();
		if (len == 0) {
			return;
		}
		int max = *max_element(num.begin(), num.end());
		for (int exp = 1; max / exp > 0; exp *= 10) {
			r.radixHelp(num,exp);
		}

	}
};
/*
int main() {
	solution s;
	vector<int> num;
	cout << "ԭ�����ǣ�5,3,8,6,4" << endl;
	num = { 5,3,8,6,4 };
	s.bubbleSort(num);
	s.printOut(num);
	num = { 5,3,8,6,4 };
	s.selectSort(num);
	s.printOut(num);
	num = { 5,3,8,6,4 };
	s.insertSort(num);
	s.printOut(num);
	num = { 5,3,8,6,4 };
	s.quickSort(num);
	s.printOut(num);
	num = { 5,3,8,6,4 };
	s.heapSort(num);
	s.printOut(num);
	num = { 5,3,8,6,4 };
	s.shellSort(num);
	s.printOut(num);
	num = { 5,3,8,6,4 };
	s.mergeSort(num);
	s.printOut(num);
	num = { 5,3,8,6,4 };
	s.countSort(num);
	s.printOut(num);
	num = { 51,33,82,64,45 };
	s.radixSort(num);
	s.printOut(num);
	while (1);
	return 0;
}*/