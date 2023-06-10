function emptySheet() {
    let sheetInfo = cellData[selectedSheet];
    for (let i of Object.Keys(sheetInfo)) {
        for (let j of Object.Keys(sheetInfo[i])) {
            $(`#row-${i}-col-${j}`).text("");
            $(`#row-${i}-col-${j}`).css("background-color", "#ffffff");
            $(`#row-${i}-col-${j}`).css("color", "#000000");
            $(`#row-${i}-col-${j}`).css("text-align", "left");
            $(`#row-${i}-col-${j}`).css("font-weight", "");
            $(`#row-${i}-col-${j}`).css("font-style", "");
            $(`#row-${i}-col-${j}`).css("text-decoration", "");
            $(`#row-${i}-col-${j}`).css("font-family", "Noto Sans");
            $(`#row-${i}-col-${j}`).css("font-size", "14px");
        }
    }
}

function loadSheet() {
    let sheetInfo = cellData[selectedSheet];
    for (let i of Object.Keys(sheetInfo)) {
        for (let j of Object.Keys(sheetInfo[i])) {
            let cellInfo = cellData[selectedSheet][i][j];
            $(`#row-${i}-col-${j}`).text(cellInfo["text"]);
            $(`#row-${i}-col-${j}`).css("background-color", cellInfo["background-color"]);
            $(`#row-${i}-col-${j}`).css("color", cellInfo["color"]);
            $(`#row-${i}-col-${j}`).css("text-align", cellInfo["text-align"]);
            $(`#row-${i}-col-${j}`).css("font-weight", cellInfo["font-weight"]);
            $(`#row-${i}-col-${j}`).css("font-style", cellInfo["font-style"]);
            $(`#row-${i}-col-${j}`).css("text-decoration", cellInfo["text-decoration"]);
            $(`#row-${i}-col-${j}`).css("font-family", cellInfo["font-family"]);
            $(`#row-${i}-col-${j}`).css("font-size", cellInfo["font-size"]);
        }
    }
}
