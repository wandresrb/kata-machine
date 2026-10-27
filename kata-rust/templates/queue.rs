use std::marker::PhantomData;

pub struct Queue<T> {
    // TODO: replace with your own fields (a linked list with head and tail)
    _todo: PhantomData<T>,
}

impl<T: Clone> Queue<T> {
    pub fn new() -> Self {
        todo!()
    }

    pub fn enqueue(&mut self, item: T) {
        todo!()
    }

    pub fn deque(&mut self) -> Option<T> {
        todo!()
    }

    pub fn peek(&self) -> Option<T> {
        todo!()
    }

    pub fn len(&self) -> usize {
        todo!()
    }

    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }
}
