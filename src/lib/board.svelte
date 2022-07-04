
<script>
    
    export let selectedSwitch;
    export let selectSwitch;

    const switches = [
        [1, 1, 1],
        [1, 2.25],
    ]
</script>

<div id="board">
    {#each switches as row, rowIndex}
        <div class="row">
            {#each row as sw, switchIndex}
                <div class="switch f_high b_low" style={`width:${50*sw}px;`}>
                    {`SW`}
                    <br>
                    {`${rowIndex+1}.${switchIndex+1}`}
                </div>
            {/each}
        </div>
    {/each}
</div>

<style>
    #board {
        background-color: white;
        padding: 10px;
        width: fit-content;
        border-radius: 5px;
        border: 1px solid rgba(0, 0, 0, .5);
        font-size: 12px;
        text-decoration: underline;
        text-decoration-color: var(--f_high);
    }

    .row {
        display: flex;
        flex-direction: row;
        justify-content: space-between;
    }

    .switch {
        border-radius: 5px;
        padding: 5px;
        margin: 2px;
        height: 50px;
    }

</style>