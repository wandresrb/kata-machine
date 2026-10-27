use std::marker::PhantomData;

pub struct Stack<T> {
    // TODO: replace with your own fields (e.g. head: Option<Box<Node<T>>>, len: usize)
    _todo: PhantomData<T>,
}

impl<T: Clone> Stack<T> {
    pub fn new() -> Self {
        todo!()
    }

    pub fn push(&mut self, item: T) {
        todo!()
    }

    pub fn pop(&mut self) -> Option<T> {
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
