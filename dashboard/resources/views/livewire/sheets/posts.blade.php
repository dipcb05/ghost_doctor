@php($hum = data_get($this->posts[sizeof($this->posts)-1], 'humidity'))
@php($temp = data_get($this->posts[sizeof($this->posts)-1], 'temparature'))
@php($datetime = data_get($this->posts[sizeof($this->posts)-1], 'datetime'))

<div class = "card">
 <div class = "card-header">Current Condition of 1st Patient</div>
  <div class="mt-3 space-y-3">
    <div class="rounded-md shadow-md p-3">
        <p class="mb-1"><b>Humidity: </b> {{ $hum }}% 
        @if($hum < "50" && $hum > "20")
        <span class="badge bg-success">Safe</span>  
        @else
        <span class="badge bg-danger">Danger</span>
        @if($hum < "20")
        <a class="btn btn-primary" href="{{ route('control') }}">Room humidity is under safety level. You have to turn on the hitter, go to control panel</a>
        @elseif($hum > "50")
        <a class="btn btn-primary" href="{{ route('control') }}">Room is over hit. You have to control the air cooler, go to control panel</a>
        @endif
        @endif    
        </p>
        <p class="mb-1"><b>Room Temparature: </b>{{ $temp }}°
        @if($temp < "35" && $temp > "15")
        <span class="badge bg-success">Safe</span>
        @else
        <span class="badge bg-danger">Danger</span>
        @if($temp < "15")
        <a class="btn btn-primary" href="{{ route('control') }}">Room is Over cold. You have to turn on the hitter, go to control panel</a>
        @elseif($temp > "35")
        <a class="btn btn-primary" href="{{ route('control') }}">Room is over hit. You have to control the air cooler, go to control panel</a>
        @endif
        @endif
        </p>
    </div>
  </div>
  <div class = "card-footer">Last Collection Time: {{ $datetime }}</div>
</div>