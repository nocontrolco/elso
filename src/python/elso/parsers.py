import yfinance as yf
import quandl as qd


class StockData:
    """
    Class for retrieving and holds stock data from Yahoo Finance.
    """

    def __init__(self, symbol_name: str, is_brazil: bool = True) -> None:
        self.ticker = yf.Ticker(symbol_name + ".SA" if is_brazil else symbol_name)
        self.data = None

    def GetStockMetadata(self) -> dict:
        """
        Returns the stock metadata.
        """

        return self.ticker.info

    def LoadData(self, **kwargs):
        """
        Loads & returns historical data from Yahoo Finance.
        Common arguments:
        - start: str
        - end: str
        - period: str
        - interval: str
        """

        assert all(
            key in ["start", "end", "period", "interval"] for key in kwargs.keys()
        ), "Unknown arguments."

        # Gather history data & convert timestamp indices columns to str objects
        self.data = self.ticker.history(**kwargs)
        self.data.index = self.data.index.map(lambda x: x.strftime("%Y-%m-%d %H:%M:%S"))
        return self.data


class RatesData:
    """
    Static class for retrieving common rates data.
    Rates include: CDI, SELIC, IPCA & IGP-M.
    """

    # Quandl API Key
    qd.ApiConfig.api_key = "QnzyW97fXEfE8sZbtxb-"

    # Please for code references, see:
    # https://data.nasdaq.com/data/BCB-central-bank-of-brazil-statistical-database
    DATASET_CODES = {
        "SELIC-daily": "BCB/11",
        "SELIC-monthly": "BCB/4390",
        "SELIC-annually": "BCB/432",
        "IPCA": "BCB/433",
        "IGPM": "BCB/189",
        "CDI-daily": "BCB/12",
        "CDI-monthly": "BCB/4391",
        "CDI-annually": "BCB/4391",
    }

    @classmethod
    def LoadData(cls, **kwargs):
        """
        Loads historical rates data from the web.
        Common arguments:
        - rate_name: str
        - start_date: str
        - end_date: str
        - period: str
        """

        assert all(
            key in ["rate_name", "start_date", "end_date", "period"]
            for key in kwargs.keys()
        ), "Unknown arguments."

        rate_name = kwargs.pop("rate_name", None)
        data = {}

        # Gather history data
        if rate_name is not None:
            dataset_code = cls.DATASET_CODES[rate_name]
            data[rate_name] = qd.get(dataset_code, **kwargs)
        else:
            for rate_name in cls.DATASET_CODES.keys():
                dataset_code = cls.DATASET_CODES[rate_name]
                data[rate_name] = qd.get(dataset_code, **kwargs)

        # Convert timestamp indices columns to str objects
        for key in data.keys():
            data[key].index = data[key].index.map(lambda x: x.strftime("%Y-%m-%d"))
            data[key] = data[key].to_dict()
        return data
