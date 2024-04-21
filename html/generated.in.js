var layout = {
    title: 'Generated Surface',
     // scene: {camera: {eye: {x: 10., y: 11., z: 10}}},
    autosize: true,
    // width: 500,
    // height: 1080,
    // margin: {
    //     l: 65,
    //     r: 50,
    //     b: 65,
    //     t: 90,
    // }
};
var config = {responsive: true}
Plotly.newPlot('myDiv', data, layout, config);
//  Plotly.newPlot('myDiv', data);