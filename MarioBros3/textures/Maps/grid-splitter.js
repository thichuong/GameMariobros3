/*
 * grid-splitter.js
 *
 * This extension adds a 'BUILD THAYDUNG'S GRID DATA' (Ctrl+Shift+G) action to the Map
 * menu, which can be used to quickly split grid for your tiled-map.
 */

/* global tiled */

function addGridToObject(layersCombound, gridConfig) {
	for (let i = layersCombound.layerCount - 1; i >= 0; i--) {
		const layer = layersCombound.layerAt(i);

		if (layer.isGroupLayer) {
			addGridToObject(layer, gridConfig);
		} else if (layer.isObjectLayer) {
			for (const obj of layer.objects) {
				if (obj.shape != 0 && obj.shape != 5) continue;

				const props = obj.resolvedProperties();

				if (props.hasOwnProperty("Grid")) {
					obj.removeProperty("Grid");
				}

				let objectW = 0;
				let objectH = 0;

				if (obj.shape == 0) {
					objectW = obj.width;
					objectH = obj.height;
				} else if (obj.shape == 5){
					if (!props.hasOwnProperty("width") || !props.hasOwnProperty("height"))
						continue;
					objectW = props.width;
					objectH = props.height;
				}

				let beginX = obj.x / gridConfig.cellWidth;
				let beginY = obj.y / gridConfig.cellHeight;
				let endX = (obj.x + objectW) / gridConfig.cellWidth;
				let endY = (obj.y + objectH) / gridConfig.cellHeight;

				beginX = Math.max(0, Math.floor(beginX) - Number.isInteger(beginX));
				beginY = Math.max(0, Math.floor(beginY) - Number.isInteger(beginY));

				endX = Math.ceil(endX) + Number.isInteger(endX);
				endY = Math.ceil(endY) + Number.isInteger(endY);

				gridConfig.totalColumn = Math.max(gridConfig.totalColumn, endX);
				gridConfig.totalRow = Math.max(gridConfig.totalRow, endY);

				let grid = []

				for (let x = beginX; x < endX; x++) {
					for (let y = beginY; y < endY; y++) {
						grid.push({x: x, y: y});
					}
				}

				obj.setProperty("Grid", JSON.stringify(grid));
			}
		}
	}
}

let jumpToObject = tiled.registerAction("BuildGrid", function(/* action */) {
	const map = tiled.activeAsset;
	if (!map.isTileMap) {
		tiled.alert("Not a tile map!");
		return;
	}

	if (map.infinite) {
		tiled.alert("Not support infinity map!");
		return;
	}

	const confirmResult = tiled.confirm("Use this feature will remove all \"grid\" property in Point objects and Rectangle objects.\n Are you sure to continue?");
	if (!confirmResult) {
		tiled.alert("Action cancelled!");
		return;
	}

	const cellWidth = parseInt(tiled.prompt("Enter cell width (pixel):", "385"));
	const cellHeight = parseInt(tiled.prompt("Enter cell height (pixel):", "290"));

	const mapWidthInPixel = map.width * map.tileWidth;
	const mapHeightInPixel = map.height * map.tileHeight;

	let gridConfig = {
		cellWidth: cellWidth,
		cellHeight: cellHeight,
		mapWidthInPixel: mapWidthInPixel,
		mapHeightInPixel: mapHeightInPixel,
		totalColumn: 0,
		totalRow: 0
	}

	addGridToObject(map, gridConfig);

	map.setProperties({
		CellWidth: Math.floor(gridConfig.cellWidth),
		CellHeight: Math.floor(gridConfig.cellHeight),
		TotalColumn: gridConfig.totalColumn,
		TotalRow: gridConfig.totalRow
	});

	tiled.log(JSON.stringify({GridInfo: gridConfig}));
	tiled.alert("Tool by Chính: 18520257!");
});
jumpToObject.text = "Build Grid Data for Thầy Dũng";
jumpToObject.shortcut = "Ctrl+Shift+G";

tiled.extendMenu("Map", [
	{ separator: true },
	{ action: "BuildGrid" },
]);
