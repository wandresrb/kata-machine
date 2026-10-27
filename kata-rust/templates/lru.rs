use std::hash::Hash;
use std::marker::PhantomData;

/// Least-recently-used cache: `get` and `update` both mark the key as most recently used.
pub struct Lru<K, V> {
    // TODO: replace with your own fields (e.g. a HashMap<K, usize> into an index-linked list)
    _todo: PhantomData<(K, V)>,
}

impl<K: Hash + Eq + Clone, V: Clone> Lru<K, V> {
    pub fn new(capacity: usize) -> Self {
        todo!()
    }

    pub fn update(&mut self, key: K, value: V) {
        todo!()
    }

    pub fn get(&mut self, key: &K) -> Option<V> {
        todo!()
    }
}
