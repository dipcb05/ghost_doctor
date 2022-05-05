<div class = "card">
 <div class = "card-header">Current Condition of Patient</div>
  <div class="mt-3 space-y-3">
    <div class="rounded-md shadow-md p-3">
        <p class="mb-1"><b>Humidity Update: </b> {{ data_get($this->posts[sizeof($this->posts)-1], 'humidity') }}%</p>
        <p class="mb-1"><b>Room Temparature Update: </b>{{ data_get($this->posts[sizeof($this->posts)-1], 'temparature') }}°</p>
    </div>
  </div>
  <div class = "card-footer">Current Time: {{ data_get($this->posts[sizeof($this->posts)-1], 'datetime') }}</div>
</div>