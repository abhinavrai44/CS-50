<table class="table">
    <thead>
     <table border="1" style="width:100%">
        <tr>
            <td>Buy/Sell</td>
            <td>Symbol</td>
            <td>Shares</td>
            <td>Value</td>
            <td>Amount</td>
        </tr>
    </thead>
    <tbody>
        <?php
            if(isset($transactions))
            {        
                foreach($transactions as $transaction)
                {
                    print("<tr>");
                    print("<td>" . $transaction["buysell"] . "</td>");
                    print("<td>" . $transaction["symbol"] . "</td>");
                    print("<td>" . $transaction["shares"] . "</td>");
                    print("<td>" . $transaction["value"] . "</td>");
                    print("<td>" . $transaction["amount"] . "</td>");
                    print("</tr>\n");
                }
            }
        ?>
    </tbody>
</table>
