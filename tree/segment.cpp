template <typename T>
struct SegmentTree
{
	int N;
	T error;
	vector<T> tree;

	SegmentTree(const vector<T>& array, const T& error) : error(error)
	{
		N = array.size();
		tree.resize(N * 4);
		init(array, 0, N-1, 1);
	}

	T calc(T left, T right)
	{
		return left * right % MOD;
	}

	T init(const vector<T>& array, int left, int right, int node)
	{
		if(left == right)
			return tree[node] = array[left];

		int mid = (left + right) / 2;
		T rangeLeft = init(array, left, mid, node * 2);
		T rangeRight = init(array, mid+1, right, node * 2 + 1);
		return tree[node] = calc(rangeLeft, rangeRight);
	}

	T query(int left, int right, int node, int nodeLeft, int nodeRight)
	{
		if(right < nodeLeft || nodeRight < left)
			return error;

		if(left <= nodeLeft && nodeRight <= right)
			return tree[node];

		int mid = (nodeLeft + nodeRight) / 2;
		return calc(query(left, right, node * 2, nodeLeft, mid),
								query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	T query(int left, int right)
	{
		return query(left, right, 1, 0, N-1);
	}

	T update(int index, T& newValue, int node, int nodeLeft, int nodeRight)
	{
		if(index < nodeLeft || nodeRight < index)
			return tree[node];

		if(nodeLeft == nodeRight)
			return tree[node] = newValue;

		int mid = (nodeLeft + nodeRight) / 2;
		return tree[node] = calc(update(index, newValue, node * 2, nodeLeft, mid),
														 update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}

	T update(int index, T newValue)
	{
		return update(index, newValue, 1, 0, N-1);
	}
};