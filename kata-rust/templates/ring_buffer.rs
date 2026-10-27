use std::marker::PhantomData;

/// Growable ring buffer: `push` appends, `pop` removes the oldest item, `get(0)` is the oldest.
pub struct RingBuffer<T> {
    // TODO: replace with your own fields (e.g. buf: Vec<Option<T>>, head: usize, len: usize)
    _todo: PhantomData<T>,
}

impl<T: Clone> RingBuffer<T> {
    pub fn new() -> Self {
        todo!()
    }

    pub fn push(&mut self, item: T) {
        todo!()
    }

    pub fn pop(&mut self) -> Option<T> {
        todo!()
    }

    pub fn get(&self, idx: usize) -> Option<T> {
        todo!()
    }

    pub fn len(&self) -> usize {
        todo!()
    }

    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }
}
