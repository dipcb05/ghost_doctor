<div class="mt-3 space-y-3">
    @foreach(array_reverse($this->posts) as $post)
        <div class="rounded-md shadow-md p-3">
            <div class="d-flex w-100 justify-content-between">
                <h5 class="font-bold">{{ data_get($post, 'datetime') }}</h5>
            </div>
            <p class="mb-1">
               <b>Humidity Update: </b> {{ data_get($post, 'humidity') }}
            </p>
            <p class="mb-1">
                <b>Room Temparature Update: </b>{{ data_get($post, 'temparature') }}
            </p>
            <p class="mb-1">
            <b>Light Sensor: </b>{{ data_get($post, 'LDR') }}
            </p>
            <!-- <small>
                {{ data_get($post, 'created_at') }} {{ config('app.timezone') }}
            </small> -->
        </div>
    @endforeach
</div>
