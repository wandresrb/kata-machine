use std::hash::Hash;
use std::marker::PhantomData;

/// Hand-made hash map (hint: `std::hash::DefaultHasher` + buckets). No `std::collections`!
pub struct Map<K, V> {
    // TODO: replace with your own fields (e.g. buckets: Vec<Vec<(K, V)>>, len: usize)
    _todo: PhantomData<(K, V)>,
}

impl<K: Hash + Eq, V: Clone> Map<K, V> {
    pub fn new() -> Self {
        todo!()
    }

    pub fn get(&self, key: &K) -> Option<V> {
        todo!()
    }

    pub fn set(&mut self, key: K, value: V) {
        todo!()
    }

    pub fn delete(&mut self, key: &K) -> Option<V> {
        todo!()
    }

    pub fn size(&self) -> usize {
        todo!()
    }
}
