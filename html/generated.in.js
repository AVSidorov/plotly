var layout = {
    title: 'Generated Surface',
     // scene: {camera: {eye: {x: 10., y: 11., z: 10}}},
    autosize: false,
    width: 500,
    height: 500,
    margin: {
        l: 65,
        r: 50,
        b: 65,
        t: 90,
    }
};
Plotly.newPlot('myDiv', data, layout);
// Plotly.newPlot('myDiv', data);