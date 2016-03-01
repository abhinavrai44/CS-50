<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select name="symbol">
                <option value=''></option>
                <?php
                    foreach($positions as $position)
                    {
                        print("<option value='" . $position["symbol"] . "'>" . $position["symbol"] . "</option>");
                    }
                ?>
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
