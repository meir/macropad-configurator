
<script>
    import LayerList from "./layerlist.svelte";
    import Layer from "./layer.svelte";

    export let data = {
        layers: {
            "Default": [[0],[1],[2],[3],[4],[5]],
            "Layer 1": [[0],[1],[2],[3],[4],[5]],
            "Layer 2": [[0],[1],[2],[3],[4],[5]],
            "Layer 3": [[0],[1],[2],[3],[4],[5]]
        },
        order: ["Default", "Layer 1", "Layer 2", "Layer 3"],
    };

    let selectedLayer = data.order[0];

    const selectLayer = (name) => {
        console.log(data)
        if(!data.order.includes(name)) data.order[0];
        selectedLayer = name;
    }
</script>

<div>
    <LayerList selectLayer={selectLayer} data={data}></LayerList>
    <Layer name={selectedLayer} data={data}></Layer>
</div>

<style>
    div {
        display: flex;
        height: 100%;
    }
</style>