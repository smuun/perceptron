mod matrix;
use matrix::*;

fn main() {
    let retina: NeuronVector = vec![false; 10];
    let projection_area: NeuronVector = vec![true; 10];
    let association_area: NeuronVector = vec![false; 10];
    let responses: NeuronVector = vec![false; 10];
    dbg!(&retina);
    let retina_to_projection_area = ConnectionMatrix::new(10, 10);
    apply_connections(retina_to_projection_area, projection_area);

}
